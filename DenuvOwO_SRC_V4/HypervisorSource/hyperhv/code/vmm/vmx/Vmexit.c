/**
 * @file Vmexit.c
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief The functions for VM-Exit handler for different exit reasons
 * @details
 * @version 0.1
 * @date 2020-04-11
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "pch.h"

 /**
  * @brief Handling Access to GDTR or IDTR
  * @param VCpu The virtual processor's state
  *
  * @return VOID
  */
VOID
VmxHandle_GDTR_IDTR_ACCESS(VIRTUAL_MACHINE_STATE* VCpu)
{
    VMX_VMEXIT_INSTRUCTION_INFO_GDTR_IDTR_ACCESS AccessQualification;

    AccessQualification.AsUInt = 0x0;

    VmxVmread32P(VMCS_VMEXIT_INSTRUCTION_INFO, &AccessQualification.AsUInt);

    UINT64 CurrentCR3 = 0x0;

    UINT64 CSelector = 0x0;

    __vmx_vmread(VMCS_GUEST_CS_SELECTOR, &CSelector);

    if ((CSelector & RPL_MASK) != DPL_SYSTEM)
    {
        __vmx_vmread(VMCS_GUEST_CR3, &CurrentCR3);

        if (TargetCR3 && CurrentCR3 == TargetCR3)
        {
            if (AccessQualification.Instruction == 0x0)
            {
                __vmx_vmread(VMCS_GUEST_GDTR_LIMIT, &VCpu->TestNumber);
                VmxVmwrite64(VMCS_GUEST_GDTR_LIMIT, 0x7F);
            }
        }
    }

    UINT32 SecondaryProcBasedVmExecControls = 0;

    VmxVmread32P(VMCS_CTRL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, &SecondaryProcBasedVmExecControls);

    SecondaryProcBasedVmExecControls &= ~IA32_VMX_PROCBASED_CTLS2_DESCRIPTOR_TABLE_EXITING_FLAG;

    VmxVmwrite32(VMCS_CTRL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, SecondaryProcBasedVmExecControls);

    VmxVmwrite32(VMCS_CTRL_EXCEPTION_BITMAP, 0x27002); // #DB, #SS, #GP, #PF, #AC

    RFLAGS GuestRFlags = { .AsUInt = GetGuestRFlags() };
    IA32_DEBUGCTL_REGISTER  Debugctl = { .AsUInt = HvGetDebugctl() };

    VMX_PENDING_DEBUG_EXCEPTIONS PendingDebugExceptions;
    VMX_INTERRUPTIBILITY_STATE   InterruptibilityState;

    PendingDebugExceptions.AsUInt = HvGetPendingDebugExceptions();

    if (GuestRFlags.TrapFlag && !Debugctl.Btf)
    {
        PendingDebugExceptions.Bs = 1;
        VCpu->Test = TRUE;
    }

    else
    {
        PendingDebugExceptions.EnabledBreakpoint = 1;
    }

    PendingDebugExceptions.Rtm = 0;

    HvSetPendingDebugExceptions(PendingDebugExceptions.AsUInt);

    InterruptibilityState.AsUInt = (UINT32)HvGetInterruptibilityState();
    InterruptibilityState.BlockingByMovSs = 1;
    InterruptibilityState.BlockingBySti = 0;
    InterruptibilityState.EnclaveInterruption = 0;

    HvSetInterruptibilityState(InterruptibilityState.AsUInt);

    HvSuppressRipIncrement(VCpu);
}

/**
 * @brief Handling Access to LDTR or TR
 * @param VCpu The virtual processor's state
 *
 * @return VOID
 */
VOID
VmxHandle_LDTR_TR_ACCESS(VIRTUAL_MACHINE_STATE* VCpu)
{
    UINT32 SecondaryProcBasedVmExecControls = 0;

    VmxVmread32P(VMCS_CTRL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, &SecondaryProcBasedVmExecControls);

    SecondaryProcBasedVmExecControls &= ~IA32_VMX_PROCBASED_CTLS2_DESCRIPTOR_TABLE_EXITING_FLAG;

    VmxVmwrite32(VMCS_CTRL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, SecondaryProcBasedVmExecControls);

    VmxVmwrite32(VMCS_CTRL_EXCEPTION_BITMAP, 0x27002); // #DB, #SS, #GP, #PF, #AC

    RFLAGS GuestRFlags = { .AsUInt = GetGuestRFlags() };
    IA32_DEBUGCTL_REGISTER  Debugctl = { .AsUInt = HvGetDebugctl() };

    VMX_PENDING_DEBUG_EXCEPTIONS PendingDebugExceptions;
    VMX_INTERRUPTIBILITY_STATE   InterruptibilityState;

    PendingDebugExceptions.AsUInt = HvGetPendingDebugExceptions();

    if (GuestRFlags.TrapFlag && !Debugctl.Btf)
    {
        PendingDebugExceptions.Bs = 1;
        VCpu->Test = TRUE;
    }

    else
    {
        PendingDebugExceptions.EnabledBreakpoint = 1;
    }

    PendingDebugExceptions.Rtm = 0;

    HvSetPendingDebugExceptions(PendingDebugExceptions.AsUInt);

    InterruptibilityState.AsUInt = (UINT32)HvGetInterruptibilityState();

    InterruptibilityState.BlockingByMovSs = 1;
    InterruptibilityState.BlockingBySti = 0;
    InterruptibilityState.EnclaveInterruption = 0;

    HvSetInterruptibilityState(InterruptibilityState.AsUInt);

    HvSuppressRipIncrement(VCpu);
}

/**
 * @brief Handle Cpuid Vmexits
 *
 * @param VCpu The virtual processor's state
 * @return VOID
 */
VOID
VmxHandleCpuid(VIRTUAL_MACHINE_STATE* VCpu)
{
    INT32       CpuInfo[4];
    PGUEST_REGS Regs = VCpu->Regs;

    int leaf, subLeaf;

    leaf = (INT32)(VCpu->Regs->rax);
    subLeaf = (INT32)(VCpu->Regs->rcx);

    UINT64 CurrentCR3 = 0x0;

    UINT64 CsSelector = 0x0;

    __vmx_vmread(VMCS_GUEST_CS_SELECTOR, &CsSelector);

    if ((CsSelector & RPL_MASK) != DPL_SYSTEM)
    {
        if (VCpu->Regs->rax == 0x69696969)
        {
            if (!TargetCR3)
            {
                __vmx_vmread(VMCS_GUEST_CR3, &CurrentCR3);

                UINT64 DirectoryTableBase = LayoutGetCurrentProcessCr3().Flags;

                if (DirectoryTableBase == CurrentCR3)
                {
                    __vmx_vmread(VMCS_GUEST_CR3, &TargetCR3);
                }
            }

            goto doCpuid;
        }

        __vmx_vmread(VMCS_GUEST_CR3, &CurrentCR3);

        if (TargetCR3 && CurrentCR3 == TargetCR3)
        {
            if (VCpu->Regs->rax == 0x1337)
            {
                if (!TrackedProcessId)
                {
                    TargetProcessId = VCpu->Regs->rdx;
                }

                goto doCpuid;
            }

            if (VCpu->Regs->rax == 0x336933)
            {
                if (!TargetSysHandler)
                {
                    TargetSysHandler = VCpu->Regs->rcx;
                }

                goto doCpuid;
            }

            if (leaf == 0x1) //do not modify the included values
            {
                VCpu->Regs->rax = 0x000A0655;
                VCpu->Regs->rbx = 0x00200800;
                //VCpu->Regs->rcx = 0x73FAFBFF; //0x7FFAFBFF for XGETBV support == 1 (bit 26)
                VCpu->Regs->rcx = 0x73FAFBFF & ~((1 << 12) | (1 << 25) | (1 << 26) | (1 << 27) | (1 << 28) | (1 << 29) | (1 << 30)); // Disabled FMA3, AES, XSAVE, OSXSAVE, AVX, F16C, RDRAND
                VCpu->Regs->rdx = 0xBFEBFBFF;

                return;
            }

            if (leaf == 0x80000002)
            {
                VCpu->Regs->rax = 'uneD';
                VCpu->Regs->rbx = 'OwOv';
                VCpu->Regs->rcx = 'UPC ';
                VCpu->Regs->rdx = '1 @ ';

                return;
            }

            if (leaf == 0x80000003)
            {
                VCpu->Regs->rax = ' 733';
                VCpu->Regs->rbx = 'zHG';
                VCpu->Regs->rcx = 0;
                VCpu->Regs->rdx = 0;

                return;
            }

            if (leaf == 0x80000004)
            {
                VCpu->Regs->rax = 0;
                VCpu->Regs->rbx = 0;
                VCpu->Regs->rcx = 0;
                VCpu->Regs->rdx = 0;

                return;
            }
        }
    }

    doCpuid:

    //
    // Otherwise, issue the CPUID to the logical processor based on the indexes
    // on the VP's GPRs.
    //
    __cpuidex(CpuInfo, (INT32)Regs->rax, (INT32)Regs->rcx);

    //
    // check whether we are in transparent mode or not
    // if we are in transparent mode then ignore the
    // cpuid modifications e.g. hyperviosr name or bit
    //
    if (!g_CheckForFootprints)
    {
        //
        // Check if this was CPUID 1h, which is the features request
        //
        if (Regs->rax == CPUID_PROCESSOR_AND_PROCESSOR_FEATURE_IDENTIFIERS)
        {
            //
            // Set the Hypervisor Present-bit in RCX, which Intel and AMD have both
            // reserved for this indication
            //
            CpuInfo[2] |= HYPERV_HYPERVISOR_PRESENT_BIT;
        }
        else if (Regs->rax == CPUID_HV_VENDOR_AND_MAX_FUNCTIONS)
        {
            //
            // Return a maximum supported hypervisor CPUID leaf range and a vendor
            // ID signature as required by the spec
            //

            CpuInfo[0] = HYPERV_CPUID_INTERFACE;
            CpuInfo[1] = 'epyH'; // [HyperDbg]
            CpuInfo[2] = 'gbDr';
            CpuInfo[3] = 0;
        }
        else if (Regs->rax == HYPERV_CPUID_INTERFACE)
        {
            //
            // Return non Hv#1 value. This indicate that our hypervisor does NOT
            // conform to the Microsoft hypervisor interface.
            //

            CpuInfo[0] = '0#vH'; // Hv#0
            CpuInfo[1] = CpuInfo[2] = CpuInfo[3] = 0;
        }
    }
    else
    {
        TransparentCheckAndModifyCpuid(Regs, CpuInfo);
    }

    //
    // Copy the values from the logical processor registers into the VP GPRs
    //
    Regs->rax = CpuInfo[0];
    Regs->rbx = CpuInfo[1];
    Regs->rcx = CpuInfo[2];
    Regs->rdx = CpuInfo[3];
}

/**
 * @brief VM-Exit handler for different exit reasons
 *
 * @param GuestRegs Registers that are automatically saved by AsmVmexitHandler (HOST_RIP)
 * @return BOOLEAN Return True if VMXOFF executed (not in vmx anymore),
 *  or return false if we are still in vmx (so we should use vm resume)
 */
BOOLEAN
VmxVmexitHandler(_Inout_ PGUEST_REGS GuestRegs)
{
    UINT32                  ExitReason = 0;
    BOOLEAN                 Result     = FALSE;
    VIRTUAL_MACHINE_STATE * VCpu       = NULL;

    //
    // *********** SEND MESSAGE AFTER WE SET THE STATE ***********
    //
    VCpu = &g_GuestState[KeGetCurrentProcessorNumberEx(NULL)];

    //
    // Set the registers (general-purpose and XMM)
    //
    VCpu->Regs    = GuestRegs;
    VCpu->XmmRegs = (GUEST_XMM_REGS *)(((CHAR *)GuestRegs) + sizeof(GUEST_REGS));

    //
    // Indicates we are in Vmx root mode in this logical core
    //
    VCpu->IsOnVmxRootMode = TRUE;

    //
    // read the exit reason and exit qualification
    //
    VmxVmread32P(VMCS_EXIT_REASON, &ExitReason);
    ExitReason &= 0xffff;

    //
    // Save the exit reason
    //
    VCpu->ExitReason = ExitReason;

    //
    // Increase the RIP by default
    //
    VCpu->IncrementRip = TRUE;

    //
    // Save the current rip
    //
    __vmx_vmread(VMCS_GUEST_RIP, &VCpu->LastVmexitRip);

    //
    // Set the rsp in general purpose registers structure
    //
    __vmx_vmread(VMCS_GUEST_RSP, &VCpu->Regs->rsp);

    //
    // Read the exit qualification
    //
    VmxVmread32P(VMCS_EXIT_QUALIFICATION, &VCpu->ExitQualification);

    //
    // Debugging purpose
    //
    // LogInfo("VM_EXIT_REASON : 0x%x", ExitReason);
    // LogInfo("VMCS_EXIT_QUALIFICATION : 0x%llx", VCpu->ExitQualification);
    //

    switch (ExitReason)
    {
    case VMX_EXIT_REASON_GDTR_IDTR_ACCESS:
    {
        VmxHandle_GDTR_IDTR_ACCESS(VCpu);

        break;
    }

    case VMX_EXIT_REASON_LDTR_TR_ACCESS:
    {
        VmxHandle_LDTR_TR_ACCESS(VCpu);

        break;
    }

    case VMX_EXIT_REASON_EXECUTE_CPUID:
    {
        //
        // Dispatch and trigger the CPUID instruction events
        //
        VmxHandleCpuid(VCpu);

        break;
    }

    case VMX_EXIT_REASON_TRIPLE_FAULT: //"Oh baby a triple!!!"
    {
        VmxHandleTripleFaults(VCpu);

        break;
    }

        //
        // 25.1.2  Instructions That Cause VM Exits Unconditionally
        // The following instructions cause VM exits when they are executed in VMX non-root operation: CPUID, GETSEC,
        // INVD, and XSETBV. This is also true of instructions introduced with VMX, which include: INVEPT, INVVPID,
        // VMCALL, VMCLEAR, VMLAUNCH, VMPTRLD, VMPTRST, VMRESUME, VMXOFF, and VMXON.
        //

    case VMX_EXIT_REASON_EXECUTE_VMCLEAR:
    case VMX_EXIT_REASON_EXECUTE_VMPTRLD:
    case VMX_EXIT_REASON_EXECUTE_VMPTRST:
    case VMX_EXIT_REASON_EXECUTE_VMREAD:
    case VMX_EXIT_REASON_EXECUTE_VMRESUME:
    case VMX_EXIT_REASON_EXECUTE_VMWRITE:
    case VMX_EXIT_REASON_EXECUTE_VMXOFF:
    case VMX_EXIT_REASON_EXECUTE_VMXON:
    case VMX_EXIT_REASON_EXECUTE_VMLAUNCH:
    {
        //
        // cf=1 indicate vm instructions fail
        //
        // UINT64 Rflags = 0;
        // __vmx_vmread(VMCS_GUEST_RFLAGS, &Rflags);
        // VmxVmwrite64(VMCS_GUEST_RFLAGS, Rflags | 0x1);

        //
        // Handle unconditional vm-exits (inject #ud)
        //
        EventInjectUndefinedOpcode(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EXECUTE_INVEPT:
    case VMX_EXIT_REASON_EXECUTE_INVVPID:
    case VMX_EXIT_REASON_EXECUTE_GETSEC:
    case VMX_EXIT_REASON_EXECUTE_INVD:
    {
        //
        // Handle unconditional vm-exits (inject #ud)
        //
        EventInjectUndefinedOpcode(VCpu);

        break;
    }
    case VMX_EXIT_REASON_MOV_CR:
    {
        //
        // Handle vm-exit, events, dispatches and perform changes from CR access
        //
        DispatchEventMovToFromControlRegisters(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EXECUTE_RDMSR:
    {
        //
        // Handle vm-exit, events, dispatches and perform MSR read
        //
        MsrHandleRdmsrVmexit(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EXECUTE_WRMSR:
    {
        //
        // Handle vm-exit, events, dispatches and perform changes
        //
        MsrHandleWrmsrVmexit(VCpu);

        break;
    }
    case VMX_EXIT_REASON_IO_SMI:
    case VMX_EXIT_REASON_SMI:
    {
        //
        // Handle SMI and IO-SMI (should never happen in normal cases)
        //
        LogInfo("VM-exit reason SMM %llx | qual: %llx", ExitReason, VCpu->ExitQualification);

        break;
    }

    case VMX_EXIT_REASON_EXECUTE_IO_INSTRUCTION:
    {
        //
        // Dispatch and trigger the I/O instruction events
        //
        DispatchEventIO(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EPT_VIOLATION:
    {
        //
        // Handle EPT violation
        //
        if (EptHandleEptViolation(VCpu) == FALSE)
        {
            LogError("Err, there were errors in handling EPT violation");
        }

        break;
    }
    case VMX_EXIT_REASON_EPT_MISCONFIGURATION:
    {
        //
        // Handle EPT misconfiguration (should never happen)
        //
        EptHandleMisconfiguration();

        break;
    }
    case VMX_EXIT_REASON_EXECUTE_VMCALL:
    {
        //
        // Handle vm-exits of VMCALLs
        //
        DispatchEventVmcall(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EXCEPTION_OR_NMI:
    {
        //
        // Handle the EXCEPTION injection/emulation
        //
        DispatchEventException(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EXTERNAL_INTERRUPT:
    {
        //
        // Call the external-interrupt handler
        //
        DispatchEventExternalInterrupts(VCpu);

        break;
    }
    case VMX_EXIT_REASON_INTERRUPT_WINDOW:
    {
        //
        // Call the interrupt-window exiting handler to re-inject the previous
        // interrupts or disable the interrupt-window exiting bit
        //
        IdtEmulationHandleInterruptWindowExiting(VCpu);

        break;
    }
    case VMX_EXIT_REASON_NMI_WINDOW:
    {
        //
        // Call the NMI-window exiting handler
        //
        IdtEmulationHandleNmiWindowExiting(VCpu);

        break;
    }
    case VMX_EXIT_REASON_MONITOR_TRAP_FLAG:
    {
        //
        // General handler to monitor trap flags (MTF)
        //
        MtfHandleVmexit(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EXECUTE_HLT:
    {
        //
        // We don't wanna halt
        //

        //
        //__halt();
        //
        break;
    }
    case VMX_EXIT_REASON_EXECUTE_RDTSC:
    case VMX_EXIT_REASON_EXECUTE_RDTSCP:

    {
        //
        // Check whether we are allowed to change the registers
        // and emulate rdtsc or not
        //
        DispatchEventTsc(VCpu, ExitReason == VMX_EXIT_REASON_EXECUTE_RDTSCP ? TRUE : FALSE);

        break;
    }
    case VMX_EXIT_REASON_EXECUTE_RDPMC:
    {
        //
        // Handle RDPMC's events, triggers and dispatches (emulate RDPMC)
        //
        DispatchEventRdpmc(VCpu);

        break;
    }
    case VMX_EXIT_REASON_MOV_DR:
    {
        //
        // Trigger, dispatch and handle the event
        //
        DispatchEventMov2DebugRegs(VCpu);

        break;
    }
    case VMX_EXIT_REASON_EXECUTE_XSETBV:
    {
        //
        // Dispatch and trigger the XSETBV instruction events
        //
        DispatchEventXsetbv(VCpu);

        break;
    }
    case VMX_EXIT_REASON_VMX_PREEMPTION_TIMER_EXPIRED:
    {
        //
        // Handle the VMX preemption timer vm-exit
        //
        VmxHandleVmxPreemptionTimerVmexit(VCpu);

        break;
    }
    case VMX_EXIT_REASON_PAGE_MODIFICATION_LOG_FULL:
    {
        //
        // Handle page-modification log
        //
        DirtyLoggingHandleVmexits(VCpu);

        break;
    }
    default:
    {
        //
        // Not handled vm-exit
        //
        LogError("Err, unknown vmexit, reason : 0x%llx", ExitReason);

        break;
    }
    }

    if (!VCpu->VmxoffState.IsVmxoffExecuted && VCpu->ExitReason != VMX_EXIT_REASON_GDTR_IDTR_ACCESS && VCpu->ExitReason != VMX_EXIT_REASON_LDTR_TR_ACCESS)
    {
        HvHandleTrapFlag();
    }

    //
    // Check whether we need to increment the guest's ip or not
    // Also, we should not increment rip if a vmxoff executed
    //
    if (!VCpu->VmxoffState.IsVmxoffExecuted && VCpu->IncrementRip)
    {
        HvResumeToNextInstruction();
    }

    //
    // Check for vmxoff request
    //
    if (VCpu->VmxoffState.IsVmxoffExecuted)
    {
        Result = TRUE;
    }

    //
    // Set indicator of Vmx non root mode to false
    //
    VCpu->IsOnVmxRootMode = FALSE;

    //
    // By default it's FALSE, if we want to exit vmx then it's TRUE
    //
    return Result;
}
