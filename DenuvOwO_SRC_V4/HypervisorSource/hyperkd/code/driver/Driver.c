/**
 * @file Driver.c
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief The project entry
 * @details This file contains major functions and all the interactions
 * with usermode codes are managed from here.
 * e.g debugger commands and extension commands
 * @version 0.1
 * @date 2020-04-10
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "pch.h"

EXTERN_C
NTSTATUS
NTAPI
PsAcquireProcessExitSynchronization(
    _In_ PEPROCESS Process
);

EXTERN_C
VOID
NTAPI
PsReleaseProcessExitSynchronization(
    _In_ PEPROCESS Process
);

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemProcessInformation = 5,
    SystemProcessorPerformanceInformation = 8,
    SystemInterruptInformation = 23,
    SystemExceptionInformation = 33,
    SystemRegistryQuotaInformation = 37,
    SystemLookasideInformation = 45,
    SystemCodeIntegrityInformation = 103,
    SystemPolicyInformation = 134,
} SYSTEM_INFORMATION_CLASS;

#define SystemKernelVaShadowInformation     (SYSTEM_INFORMATION_CLASS)196

__kernel_entry NTSTATUS
NTAPI
NtQuerySystemInformation(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG SystemInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef struct _SYSTEM_KERNEL_VA_SHADOW_INFORMATION
{
    struct
    {
        ULONG KvaShadowEnabled : 1;
        ULONG KvaShadowUserGlobal : 1;
        ULONG KvaShadowPcid : 1;
        ULONG KvaShadowInvpcid : 1;
        ULONG KvaShadowRequired : 1;
        ULONG KvaShadowRequiredAvailable : 1;
        ULONG InvalidPteBit : 6;
        ULONG L1DataCacheFlushSupported : 1;
        ULONG L1TerminalFaultMitigationPresent : 1;
        ULONG Reserved : 18;
    } KvaShadowFlags;
} SYSTEM_KERNEL_VA_SHADOW_INFORMATION, * PSYSTEM_KERNEL_VA_SHADOW_INFORMATION;


PVOID g_PowerCallbackRegistration;

VOID
PowerCallback (
    _In_opt_ PVOID CallbackContext,
    _In_opt_ PVOID Argument1,
    _In_opt_ PVOID Argument2
    )
{
    UNREFERENCED_PARAMETER(CallbackContext);

    //
    // Ignore non-Sx changes
    //
    if (Argument1 != (PVOID)PO_CB_SYSTEM_STATE_LOCK)
    {
        return;
    }

    //
    // Check if this is S0->Sx, or Sx->S0
    //
    if (ARGUMENT_PRESENT(Argument2))
    {
        //
        // Reload the hypervisor
        //
        LoaderInitVmmAndDebugger();
    }
    else
    {
        //
        // Unload the hypervisor
        //
        VmFuncUninitVmm();
    }
}

BOOLEAN
IsKVAShadowDisabled()
{
    SYSTEM_KERNEL_VA_SHADOW_INFORMATION kvaInfo = { 0 };

    NTSTATUS KvaResult = NtQuerySystemInformation(SystemKernelVaShadowInformation, &kvaInfo, sizeof(kvaInfo), NULL);

    if (!NT_SUCCESS(KvaResult))
    {
        return TRUE;
    }

    else
    {
        if (kvaInfo.KvaShadowFlags.KvaShadowEnabled)
        {
            return FALSE;
        }

        else
        {
            return TRUE;
        }
    }
}

/**
 * @brief Main Driver Entry in the case of driver load
 *
 * @param DriverObject
 * @param RegistryPath
 * @return NTSTATUS
 */
NTSTATUS
DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryPath)
{
    NTSTATUS       Ntstatus      = STATUS_SUCCESS;
    PCALLBACK_OBJECT callbackObject;
    UNICODE_STRING callbackName =
        RTL_CONSTANT_STRING(L"\\Callback\\PowerState");
    OBJECT_ATTRIBUTES objectAttributes =
        RTL_CONSTANT_OBJECT_ATTRIBUTES(&callbackName,
                                       OBJ_CASE_INSENSITIVE |
                                       OBJ_KERNEL_HANDLE);


    NTSTATUS ThreadStatus = STATUS_SUCCESS;

    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = DrvUnload;

    //
    // Opt-in to using non-executable pool memory on Windows 8 and later.
    // https://msdn.microsoft.com/en-us/library/windows/hardware/hh920402(v=vs.85).aspx
    //
    ExInitializeDriverRuntime(DrvRtPoolNxOptIn);

    if (!IsKVAShadowDisabled())
    {
        return STATUS_HV_FEATURE_UNAVAILABLE;
    }

    //
    // Create the power state callback
    //
    Ntstatus = ExCreateCallback(&callbackObject, &objectAttributes, FALSE, TRUE);
    if (!NT_SUCCESS(Ntstatus))
    {
        return Ntstatus;
    }

    //
    // Now register our routine with this callback
    //
    g_PowerCallbackRegistration = ExRegisterCallback(callbackObject,
                                                     PowerCallback,
                                                     NULL);

    //
    // Dereference it in both cases -- either it's registered, so that is now
    // taking a reference, and we'll unregister later, or it failed to register
    // so we failing now, and it's gone.
    //
    ObDereferenceObject(callbackObject);

    //
    // Fail if we couldn't register the power callback
    //
    if (g_PowerCallbackRegistration == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    if (LoaderInitVmmAndDebugger())
    {
        ThreadStatus = PsCreateSystemThread(&CounterThreadHandle, 0, 0, 0, 0, CounterUpdater, NULL);

        if (!NT_SUCCESS(ThreadStatus))
        {
            ExUnregisterCallback(g_PowerCallbackRegistration);
            return STATUS_HV_FEATURE_UNAVAILABLE;
        }

        return STATUS_SUCCESS;
    }

    else
    {
        ExUnregisterCallback(g_PowerCallbackRegistration);
        return STATUS_HV_FEATURE_UNAVAILABLE;
    }
}

/**
 * @brief Run in the case of driver unload to unregister the devices
 *
 * @param DriverObject
 * @return VOID
 */
VOID
DrvUnload(PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    if (CounterThreadHandle)
    {
        PETHREAD CounterThread;
        ObReferenceObjectByHandle(CounterThreadHandle, NULL, *PsThreadType, KernelMode, (PVOID*)&CounterThread, NULL);
        StopCounterThread = TRUE;

        if (NotifyRoutineActive)
        {
            ProcessExitCleanup = TRUE;
        }

        KeWaitForSingleObject(CounterThread, Executive, KernelMode, FALSE, NULL);
        ObDereferenceObject(CounterThread);
        ZwClose(CounterThreadHandle);
        CounterThreadHandle = NULL;
    }
   
    ExUnregisterCallback(g_PowerCallbackRegistration);

    VmFuncUninitVmm();
}