#ifndef _IA32_H
#define _IA32_H

typedef union
{
  struct
  {
    UINT64 VirtualModeExtensions                                   : 1;
#define CR4_VIRTUAL_MODE_EXTENSIONS_BIT                              0
#define CR4_VIRTUAL_MODE_EXTENSIONS_FLAG                             0x01
#define CR4_VIRTUAL_MODE_EXTENSIONS_MASK                             0x01
#define CR4_VIRTUAL_MODE_EXTENSIONS(_)                               (((_) >> 0) & 0x01)

    UINT64 ProtectedModeVirtualInterrupts                          : 1;
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS_BIT                    1
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS_FLAG                   0x02
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS_MASK                   0x01
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS(_)                     (((_) >> 1) & 0x01)

    UINT64 TimestampDisable                                        : 1;
#define CR4_TIMESTAMP_DISABLE_BIT                                    2
#define CR4_TIMESTAMP_DISABLE_FLAG                                   0x04
#define CR4_TIMESTAMP_DISABLE_MASK                                   0x01
#define CR4_TIMESTAMP_DISABLE(_)                                     (((_) >> 2) & 0x01)

    UINT64 DebuggingExtensions                                     : 1;
#define CR4_DEBUGGING_EXTENSIONS_BIT                                 3
#define CR4_DEBUGGING_EXTENSIONS_FLAG                                0x08
#define CR4_DEBUGGING_EXTENSIONS_MASK                                0x01
#define CR4_DEBUGGING_EXTENSIONS(_)                                  (((_) >> 3) & 0x01)

    UINT64 PageSizeExtensions                                      : 1;
#define CR4_PAGE_SIZE_EXTENSIONS_BIT                                 4
#define CR4_PAGE_SIZE_EXTENSIONS_FLAG                                0x10
#define CR4_PAGE_SIZE_EXTENSIONS_MASK                                0x01
#define CR4_PAGE_SIZE_EXTENSIONS(_)                                  (((_) >> 4) & 0x01)

    UINT64 PhysicalAddressExtension                                : 1;
#define CR4_PHYSICAL_ADDRESS_EXTENSION_BIT                           5
#define CR4_PHYSICAL_ADDRESS_EXTENSION_FLAG                          0x20
#define CR4_PHYSICAL_ADDRESS_EXTENSION_MASK                          0x01
#define CR4_PHYSICAL_ADDRESS_EXTENSION(_)                            (((_) >> 5) & 0x01)

    UINT64 MachineCheckEnable                                      : 1;
#define CR4_MACHINE_CHECK_ENABLE_BIT                                 6
#define CR4_MACHINE_CHECK_ENABLE_FLAG                                0x40
#define CR4_MACHINE_CHECK_ENABLE_MASK                                0x01
#define CR4_MACHINE_CHECK_ENABLE(_)                                  (((_) >> 6) & 0x01)

    UINT64 PageGlobalEnable                                        : 1;
#define CR4_PAGE_GLOBAL_ENABLE_BIT                                   7
#define CR4_PAGE_GLOBAL_ENABLE_FLAG                                  0x80
#define CR4_PAGE_GLOBAL_ENABLE_MASK                                  0x01
#define CR4_PAGE_GLOBAL_ENABLE(_)                                    (((_) >> 7) & 0x01)

    UINT64 PerformanceMonitoringCounterEnable                      : 1;
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE_BIT                8
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE_FLAG               0x100
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE_MASK               0x01
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE(_)                 (((_) >> 8) & 0x01)

    UINT64 OsFxsaveFxrstorSupport                                  : 1;
#define CR4_OS_FXSAVE_FXRSTOR_SUPPORT_BIT                            9
#define CR4_OS_FXSAVE_FXRSTOR_SUPPORT_FLAG                           0x200
#define CR4_OS_FXSAVE_FXRSTOR_SUPPORT_MASK                           0x01
#define CR4_OS_FXSAVE_FXRSTOR_SUPPORT(_)                             (((_) >> 9) & 0x01)

    UINT64 OsXmmExceptionSupport                                   : 1;
#define CR4_OS_XMM_EXCEPTION_SUPPORT_BIT                             10
#define CR4_OS_XMM_EXCEPTION_SUPPORT_FLAG                            0x400
#define CR4_OS_XMM_EXCEPTION_SUPPORT_MASK                            0x01
#define CR4_OS_XMM_EXCEPTION_SUPPORT(_)                              (((_) >> 10) & 0x01)

    UINT64 UsermodeInstructionPrevention                           : 1;
#define CR4_USERMODE_INSTRUCTION_PREVENTION_BIT                      11
#define CR4_USERMODE_INSTRUCTION_PREVENTION_FLAG                     0x800
#define CR4_USERMODE_INSTRUCTION_PREVENTION_MASK                     0x01
#define CR4_USERMODE_INSTRUCTION_PREVENTION(_)                       (((_) >> 11) & 0x01)

    UINT64 LinearAddresses57Bit                                    : 1;
#define CR4_LINEAR_ADDRESSES_57_BIT_BIT                              12
#define CR4_LINEAR_ADDRESSES_57_BIT_FLAG                             0x1000
#define CR4_LINEAR_ADDRESSES_57_BIT_MASK                             0x01
#define CR4_LINEAR_ADDRESSES_57_BIT(_)                               (((_) >> 12) & 0x01)

    UINT64 VmxEnable                                               : 1;
#define CR4_VMX_ENABLE_BIT                                           13
#define CR4_VMX_ENABLE_FLAG                                          0x2000
#define CR4_VMX_ENABLE_MASK                                          0x01
#define CR4_VMX_ENABLE(_)                                            (((_) >> 13) & 0x01)

    UINT64 SmxEnable                                               : 1;
#define CR4_SMX_ENABLE_BIT                                           14
#define CR4_SMX_ENABLE_FLAG                                          0x4000
#define CR4_SMX_ENABLE_MASK                                          0x01
#define CR4_SMX_ENABLE(_)                                            (((_) >> 14) & 0x01)
    UINT64 Reserved1                                               : 1;

    UINT64 FsgsbaseEnable                                          : 1;
#define CR4_FSGSBASE_ENABLE_BIT                                      16
#define CR4_FSGSBASE_ENABLE_FLAG                                     0x10000
#define CR4_FSGSBASE_ENABLE_MASK                                     0x01
#define CR4_FSGSBASE_ENABLE(_)                                       (((_) >> 16) & 0x01)

    UINT64 PcidEnable                                              : 1;
#define CR4_PCID_ENABLE_BIT                                          17
#define CR4_PCID_ENABLE_FLAG                                         0x20000
#define CR4_PCID_ENABLE_MASK                                         0x01
#define CR4_PCID_ENABLE(_)                                           (((_) >> 17) & 0x01)

    UINT64 OsXsave                                                 : 1;
#define CR4_OS_XSAVE_BIT                                             18
#define CR4_OS_XSAVE_FLAG                                            0x40000
#define CR4_OS_XSAVE_MASK                                            0x01
#define CR4_OS_XSAVE(_)                                              (((_) >> 18) & 0x01)

    UINT64 KeyLockerEnable                                         : 1;
#define CR4_KEY_LOCKER_ENABLE_BIT                                    19
#define CR4_KEY_LOCKER_ENABLE_FLAG                                   0x80000
#define CR4_KEY_LOCKER_ENABLE_MASK                                   0x01
#define CR4_KEY_LOCKER_ENABLE(_)                                     (((_) >> 19) & 0x01)

    UINT64 SmepEnable                                              : 1;
#define CR4_SMEP_ENABLE_BIT                                          20
#define CR4_SMEP_ENABLE_FLAG                                         0x100000
#define CR4_SMEP_ENABLE_MASK                                         0x01
#define CR4_SMEP_ENABLE(_)                                           (((_) >> 20) & 0x01)

    UINT64 SmapEnable                                              : 1;
#define CR4_SMAP_ENABLE_BIT                                          21
#define CR4_SMAP_ENABLE_FLAG                                         0x200000
#define CR4_SMAP_ENABLE_MASK                                         0x01
#define CR4_SMAP_ENABLE(_)                                           (((_) >> 21) & 0x01)

    UINT64 ProtectionKeyEnable                                     : 1;
#define CR4_PROTECTION_KEY_ENABLE_BIT                                22
#define CR4_PROTECTION_KEY_ENABLE_FLAG                               0x400000
#define CR4_PROTECTION_KEY_ENABLE_MASK                               0x01
#define CR4_PROTECTION_KEY_ENABLE(_)                                 (((_) >> 22) & 0x01)

    UINT64 ControlFlowEnforcementEnable                            : 1;
#define CR4_CONTROL_FLOW_ENFORCEMENT_ENABLE_BIT                      23
#define CR4_CONTROL_FLOW_ENFORCEMENT_ENABLE_FLAG                     0x800000
#define CR4_CONTROL_FLOW_ENFORCEMENT_ENABLE_MASK                     0x01
#define CR4_CONTROL_FLOW_ENFORCEMENT_ENABLE(_)                       (((_) >> 23) & 0x01)

    UINT64 ProtectionKeyForSupervisorModeEnable                    : 1;
#define CR4_PROTECTION_KEY_FOR_SUPERVISOR_MODE_ENABLE_BIT            24
#define CR4_PROTECTION_KEY_FOR_SUPERVISOR_MODE_ENABLE_FLAG           0x1000000
#define CR4_PROTECTION_KEY_FOR_SUPERVISOR_MODE_ENABLE_MASK           0x01
#define CR4_PROTECTION_KEY_FOR_SUPERVISOR_MODE_ENABLE(_)             (((_) >> 24) & 0x01)
    UINT64 Reserved2                                               : 39;
  };

  UINT64 CR4;
} CR4;

typedef union
{
    struct
    {
        UINT64 Reserved1 : 3;

        /**
         * @brief Page-level Write-Through
         *
         * [Bit 3] Controls the memory type used to access the first paging structure of the current paging-structure hierarchy.
         * This bit is not used if paging is disabled, with PAE paging, or with 4-level paging if CR4.PCIDE=1.
         *
         * @see Vol3A[4.9(PAGING AND MEMORY TYPING)]
         */
        UINT64 PageLevelWriteThrough : 1;
#define CR3_PAGE_LEVEL_WRITE_THROUGH_BIT                             3
#define CR3_PAGE_LEVEL_WRITE_THROUGH_FLAG                            0x08
#define CR3_PAGE_LEVEL_WRITE_THROUGH_MASK                            0x01
#define CR3_PAGE_LEVEL_WRITE_THROUGH(_)                              (((_) >> 3) & 0x01)

        /**
         * @brief Page-level Cache Disable
         *
         * [Bit 4] Controls the memory type used to access the first paging structure of the current paging-structure hierarchy.
         * This bit is not used if paging is disabled, with PAE paging, or with 4-level paging2 if CR4.PCIDE=1.
         *
         * @see Vol3A[4.9(PAGING AND MEMORY TYPING)]
         */
        UINT64 PageLevelCacheDisable : 1;
#define CR3_PAGE_LEVEL_CACHE_DISABLE_BIT                             4
#define CR3_PAGE_LEVEL_CACHE_DISABLE_FLAG                            0x10
#define CR3_PAGE_LEVEL_CACHE_DISABLE_MASK                            0x01
#define CR3_PAGE_LEVEL_CACHE_DISABLE(_)                              (((_) >> 4) & 0x01)
        UINT64 Reserved2 : 7;

        /**
         * @brief Address of page directory
         *
         * [Bits 47:12] Physical address of the 4-KByte aligned page directory (32-bit paging) or PML4 table (64-bit paging) used
         * for linear-address translation.
         *
         * @see Vol3A[4.3(32-BIT PAGING)]
         * @see Vol3A[4.5(4-LEVEL PAGING)]
         */
        UINT64 AddressOfPageDirectory : 36;
#define CR3_ADDRESS_OF_PAGE_DIRECTORY_BIT                            12
#define CR3_ADDRESS_OF_PAGE_DIRECTORY_FLAG                           0xFFFFFFFFF000
#define CR3_ADDRESS_OF_PAGE_DIRECTORY_MASK                           0xFFFFFFFFF
#define CR3_ADDRESS_OF_PAGE_DIRECTORY(_)                             (((_) >> 12) & 0xFFFFFFFFF)
        UINT64 Reserved3 : 16;
    };

    UINT64 Flags;
} CR3;


typedef union
{
    struct
    {
        UINT64 Present : 1;
#define PT_ENTRY_64_PRESENT_BIT                                      0
#define PT_ENTRY_64_PRESENT_FLAG                                     0x01
#define PT_ENTRY_64_PRESENT_MASK                                     0x01
#define PT_ENTRY_64_PRESENT(_)                                       (((_) >> 0) & 0x01)
        UINT64 Write : 1;
#define PT_ENTRY_64_WRITE_BIT                                        1
#define PT_ENTRY_64_WRITE_FLAG                                       0x02
#define PT_ENTRY_64_WRITE_MASK                                       0x01
#define PT_ENTRY_64_WRITE(_)                                         (((_) >> 1) & 0x01)
        UINT64 Supervisor : 1;
#define PT_ENTRY_64_SUPERVISOR_BIT                                   2
#define PT_ENTRY_64_SUPERVISOR_FLAG                                  0x04
#define PT_ENTRY_64_SUPERVISOR_MASK                                  0x01
#define PT_ENTRY_64_SUPERVISOR(_)                                    (((_) >> 2) & 0x01)
        UINT64 PageLevelWriteThrough : 1;
#define PT_ENTRY_64_PAGE_LEVEL_WRITE_THROUGH_BIT                     3
#define PT_ENTRY_64_PAGE_LEVEL_WRITE_THROUGH_FLAG                    0x08
#define PT_ENTRY_64_PAGE_LEVEL_WRITE_THROUGH_MASK                    0x01
#define PT_ENTRY_64_PAGE_LEVEL_WRITE_THROUGH(_)                      (((_) >> 3) & 0x01)
        UINT64 PageLevelCacheDisable : 1;
#define PT_ENTRY_64_PAGE_LEVEL_CACHE_DISABLE_BIT                     4
#define PT_ENTRY_64_PAGE_LEVEL_CACHE_DISABLE_FLAG                    0x10
#define PT_ENTRY_64_PAGE_LEVEL_CACHE_DISABLE_MASK                    0x01
#define PT_ENTRY_64_PAGE_LEVEL_CACHE_DISABLE(_)                      (((_) >> 4) & 0x01)
        UINT64 Accessed : 1;
#define PT_ENTRY_64_ACCESSED_BIT                                     5
#define PT_ENTRY_64_ACCESSED_FLAG                                    0x20
#define PT_ENTRY_64_ACCESSED_MASK                                    0x01
#define PT_ENTRY_64_ACCESSED(_)                                      (((_) >> 5) & 0x01)
        UINT64 Dirty : 1;
#define PT_ENTRY_64_DIRTY_BIT                                        6
#define PT_ENTRY_64_DIRTY_FLAG                                       0x40
#define PT_ENTRY_64_DIRTY_MASK                                       0x01
#define PT_ENTRY_64_DIRTY(_)                                         (((_) >> 6) & 0x01)
        UINT64 LargePage : 1;
#define PT_ENTRY_64_LARGE_PAGE_BIT                                   7
#define PT_ENTRY_64_LARGE_PAGE_FLAG                                  0x80
#define PT_ENTRY_64_LARGE_PAGE_MASK                                  0x01
#define PT_ENTRY_64_LARGE_PAGE(_)                                    (((_) >> 7) & 0x01)
        UINT64 Global : 1;
#define PT_ENTRY_64_GLOBAL_BIT                                       8
#define PT_ENTRY_64_GLOBAL_FLAG                                      0x100
#define PT_ENTRY_64_GLOBAL_MASK                                      0x01
#define PT_ENTRY_64_GLOBAL(_)                                        (((_) >> 8) & 0x01)

        /**
         * [Bits 11:9] Ignored.
         */
        UINT64 Ignored1 : 3;
#define PT_ENTRY_64_IGNORED_1_BIT                                    9
#define PT_ENTRY_64_IGNORED_1_FLAG                                   0xE00
#define PT_ENTRY_64_IGNORED_1_MASK                                   0x07
#define PT_ENTRY_64_IGNORED_1(_)                                     (((_) >> 9) & 0x07)

        /**
         * [Bits 47:12] Physical address of the 4-KByte page referenced by this entry.
         */
        UINT64 PageFrameNumber : 36;
#define PT_ENTRY_64_PAGE_FRAME_NUMBER_BIT                            12
#define PT_ENTRY_64_PAGE_FRAME_NUMBER_FLAG                           0xFFFFFFFFF000
#define PT_ENTRY_64_PAGE_FRAME_NUMBER_MASK                           0xFFFFFFFFF
#define PT_ENTRY_64_PAGE_FRAME_NUMBER(_)                             (((_) >> 12) & 0xFFFFFFFFF)
        UINT64 Reserved1 : 4;

        /**
         * [Bits 58:52] Ignored.
         */
        UINT64 Ignored2 : 7;
#define PT_ENTRY_64_IGNORED_2_BIT                                    52
#define PT_ENTRY_64_IGNORED_2_FLAG                                   0x7F0000000000000
#define PT_ENTRY_64_IGNORED_2_MASK                                   0x7F
#define PT_ENTRY_64_IGNORED_2(_)                                     (((_) >> 52) & 0x7F)
        UINT64 ProtectionKey : 4;
#define PT_ENTRY_64_PROTECTION_KEY_BIT                               59
#define PT_ENTRY_64_PROTECTION_KEY_FLAG                              0x7800000000000000
#define PT_ENTRY_64_PROTECTION_KEY_MASK                              0x0F
#define PT_ENTRY_64_PROTECTION_KEY(_)                                (((_) >> 59) & 0x0F)
        UINT64 ExecuteDisable : 1;
#define PT_ENTRY_64_EXECUTE_DISABLE_BIT                              63
#define PT_ENTRY_64_EXECUTE_DISABLE_FLAG                             0x8000000000000000
#define PT_ENTRY_64_EXECUTE_DISABLE_MASK                             0x01
#define PT_ENTRY_64_EXECUTE_DISABLE(_)                               (((_) >> 63) & 0x01)
    };

    UINT64 Flags;
} PT_ENTRY_64;

typedef union _ADDRESS_TRANSLATION_HELPER
{
    //
    // Indexes to locate paging-structure entries corresponds to this virtual
    // address.
    //
    struct
    {
        UINT64 Unused : 12;         //< [11:0]
        UINT64 Pt : 9;              //< [20:12]
        UINT64 Pd : 9;              //< [29:21]
        UINT64 Pdpt : 9;            //< [38:30]
        UINT64 Pml4 : 9;            //< [47:39]
    } AsIndex;

    //
    // The page offset for each type of pages. For example, for 4KB pages, bits
    // [11:0] are treated as the page offset and Mapping4Kb can be used for it.
    //
    union
    {
        UINT64 Mapping4Kb : 12;     //< [11:0]
        UINT64 Mapping2Mb : 21;     //< [20:0]
        UINT64 Mapping1Gb : 30;     //< [29:0]
    } AsPageOffset;

    UINT64 AsUInt64;
} ADDRESS_TRANSLATION_HELPER;

typedef union
{
    struct
    {
        /**
         * [Bit 0] Present; must be 1 to reference a page-directory-pointer table.
         */
        UINT64 Present : 1;
#define PML4E_64_PRESENT_BIT                                         0
#define PML4E_64_PRESENT_FLAG                                        0x01
#define PML4E_64_PRESENT_MASK                                        0x01
#define PML4E_64_PRESENT(_)                                          (((_) >> 0) & 0x01)

        /**
         * [Bit 1] Read/write; if 0, writes may not be allowed to the 512-GByte region controlled by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Write : 1;
#define PML4E_64_WRITE_BIT                                           1
#define PML4E_64_WRITE_FLAG                                          0x02
#define PML4E_64_WRITE_MASK                                          0x01
#define PML4E_64_WRITE(_)                                            (((_) >> 1) & 0x01)

        /**
         * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 512-GByte region controlled by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Supervisor : 1;
#define PML4E_64_SUPERVISOR_BIT                                      2
#define PML4E_64_SUPERVISOR_FLAG                                     0x04
#define PML4E_64_SUPERVISOR_MASK                                     0x01
#define PML4E_64_SUPERVISOR(_)                                       (((_) >> 2) & 0x01)

        /**
         * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the page-directory-pointer table
         * referenced by this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelWriteThrough : 1;
#define PML4E_64_PAGE_LEVEL_WRITE_THROUGH_BIT                        3
#define PML4E_64_PAGE_LEVEL_WRITE_THROUGH_FLAG                       0x08
#define PML4E_64_PAGE_LEVEL_WRITE_THROUGH_MASK                       0x01
#define PML4E_64_PAGE_LEVEL_WRITE_THROUGH(_)                         (((_) >> 3) & 0x01)

        /**
         * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the page-directory-pointer table
         * referenced by this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelCacheDisable : 1;
#define PML4E_64_PAGE_LEVEL_CACHE_DISABLE_BIT                        4
#define PML4E_64_PAGE_LEVEL_CACHE_DISABLE_FLAG                       0x10
#define PML4E_64_PAGE_LEVEL_CACHE_DISABLE_MASK                       0x01
#define PML4E_64_PAGE_LEVEL_CACHE_DISABLE(_)                         (((_) >> 4) & 0x01)

        /**
         * [Bit 5] Accessed; indicates whether this entry has been used for linear-address translation.
         *
         * @see Vol3A[4.8(Accessed and Dirty Flags)]
         */
        UINT64 Accessed : 1;
#define PML4E_64_ACCESSED_BIT                                        5
#define PML4E_64_ACCESSED_FLAG                                       0x20
#define PML4E_64_ACCESSED_MASK                                       0x01
#define PML4E_64_ACCESSED(_)                                         (((_) >> 5) & 0x01)
        UINT64 Reserved1 : 1;

        /**
         * [Bit 7] Reserved (must be 0).
         */
        UINT64 MustBeZero : 1;
#define PML4E_64_MUST_BE_ZERO_BIT                                    7
#define PML4E_64_MUST_BE_ZERO_FLAG                                   0x80
#define PML4E_64_MUST_BE_ZERO_MASK                                   0x01
#define PML4E_64_MUST_BE_ZERO(_)                                     (((_) >> 7) & 0x01)

        /**
         * [Bits 11:8] Ignored.
         */
        UINT64 Ignored1 : 4;
#define PML4E_64_IGNORED_1_BIT                                       8
#define PML4E_64_IGNORED_1_FLAG                                      0xF00
#define PML4E_64_IGNORED_1_MASK                                      0x0F
#define PML4E_64_IGNORED_1(_)                                        (((_) >> 8) & 0x0F)

        /**
         * [Bits 47:12] Physical address of 4-KByte aligned page-directory-pointer table referenced by this entry.
         */
        UINT64 PageFrameNumber : 36;
#define PML4E_64_PAGE_FRAME_NUMBER_BIT                               12
#define PML4E_64_PAGE_FRAME_NUMBER_FLAG                              0xFFFFFFFFF000
#define PML4E_64_PAGE_FRAME_NUMBER_MASK                              0xFFFFFFFFF
#define PML4E_64_PAGE_FRAME_NUMBER(_)                                (((_) >> 12) & 0xFFFFFFFFF)
        UINT64 Reserved2 : 4;

        /**
         * [Bits 62:52] Ignored.
         */
        UINT64 Ignored2 : 11;
#define PML4E_64_IGNORED_2_BIT                                       52
#define PML4E_64_IGNORED_2_FLAG                                      0x7FF0000000000000
#define PML4E_64_IGNORED_2_MASK                                      0x7FF
#define PML4E_64_IGNORED_2(_)                                        (((_) >> 52) & 0x7FF)

        /**
         * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 512-GByte region
         * controlled by this entry); otherwise, reserved (must be 0).
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 ExecuteDisable : 1;
#define PML4E_64_EXECUTE_DISABLE_BIT                                 63
#define PML4E_64_EXECUTE_DISABLE_FLAG                                0x8000000000000000
#define PML4E_64_EXECUTE_DISABLE_MASK                                0x01
#define PML4E_64_EXECUTE_DISABLE(_)                                  (((_) >> 63) & 0x01)
    };

    UINT64 Flags;
} PML4E_64;

typedef union
{
    struct
    {
        /**
         * [Bit 0] Present; must be 1 to reference a page directory.
         */
        UINT64 Present : 1;
#define PDPTE_64_PRESENT_BIT                                         0
#define PDPTE_64_PRESENT_FLAG                                        0x01
#define PDPTE_64_PRESENT_MASK                                        0x01
#define PDPTE_64_PRESENT(_)                                          (((_) >> 0) & 0x01)

        /**
         * [Bit 1] Read/write; if 0, writes may not be allowed to the 1-GByte region controlled by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Write : 1;
#define PDPTE_64_WRITE_BIT                                           1
#define PDPTE_64_WRITE_FLAG                                          0x02
#define PDPTE_64_WRITE_MASK                                          0x01
#define PDPTE_64_WRITE(_)                                            (((_) >> 1) & 0x01)

        /**
         * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 1-GByte region controlled by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Supervisor : 1;
#define PDPTE_64_SUPERVISOR_BIT                                      2
#define PDPTE_64_SUPERVISOR_FLAG                                     0x04
#define PDPTE_64_SUPERVISOR_MASK                                     0x01
#define PDPTE_64_SUPERVISOR(_)                                       (((_) >> 2) & 0x01)

        /**
         * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the page directory referenced by
         * this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelWriteThrough : 1;
#define PDPTE_64_PAGE_LEVEL_WRITE_THROUGH_BIT                        3
#define PDPTE_64_PAGE_LEVEL_WRITE_THROUGH_FLAG                       0x08
#define PDPTE_64_PAGE_LEVEL_WRITE_THROUGH_MASK                       0x01
#define PDPTE_64_PAGE_LEVEL_WRITE_THROUGH(_)                         (((_) >> 3) & 0x01)

        /**
         * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the page directory referenced by
         * this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelCacheDisable : 1;
#define PDPTE_64_PAGE_LEVEL_CACHE_DISABLE_BIT                        4
#define PDPTE_64_PAGE_LEVEL_CACHE_DISABLE_FLAG                       0x10
#define PDPTE_64_PAGE_LEVEL_CACHE_DISABLE_MASK                       0x01
#define PDPTE_64_PAGE_LEVEL_CACHE_DISABLE(_)                         (((_) >> 4) & 0x01)

        /**
         * [Bit 5] Accessed; indicates whether this entry has been used for linear-address translation.
         *
         * @see Vol3A[4.8(Accessed and Dirty Flags)]
         */
        UINT64 Accessed : 1;
#define PDPTE_64_ACCESSED_BIT                                        5
#define PDPTE_64_ACCESSED_FLAG                                       0x20
#define PDPTE_64_ACCESSED_MASK                                       0x01
#define PDPTE_64_ACCESSED(_)                                         (((_) >> 5) & 0x01)
        UINT64 Reserved1 : 1;

        /**
         * [Bit 7] Page size; must be 0 (otherwise, this entry maps a 1-GByte page).
         */
        UINT64 LargePage : 1;
#define PDPTE_64_LARGE_PAGE_BIT                                      7
#define PDPTE_64_LARGE_PAGE_FLAG                                     0x80
#define PDPTE_64_LARGE_PAGE_MASK                                     0x01
#define PDPTE_64_LARGE_PAGE(_)                                       (((_) >> 7) & 0x01)

        /**
         * [Bits 11:8] Ignored.
         */
        UINT64 Ignored1 : 4;
#define PDPTE_64_IGNORED_1_BIT                                       8
#define PDPTE_64_IGNORED_1_FLAG                                      0xF00
#define PDPTE_64_IGNORED_1_MASK                                      0x0F
#define PDPTE_64_IGNORED_1(_)                                        (((_) >> 8) & 0x0F)

        /**
         * [Bits 47:12] Physical address of 4-KByte aligned page directory referenced by this entry.
         */
        UINT64 PageFrameNumber : 36;
#define PDPTE_64_PAGE_FRAME_NUMBER_BIT                               12
#define PDPTE_64_PAGE_FRAME_NUMBER_FLAG                              0xFFFFFFFFF000
#define PDPTE_64_PAGE_FRAME_NUMBER_MASK                              0xFFFFFFFFF
#define PDPTE_64_PAGE_FRAME_NUMBER(_)                                (((_) >> 12) & 0xFFFFFFFFF)
        UINT64 Reserved2 : 4;

        /**
         * [Bits 62:52] Ignored.
         */
        UINT64 Ignored2 : 11;
#define PDPTE_64_IGNORED_2_BIT                                       52
#define PDPTE_64_IGNORED_2_FLAG                                      0x7FF0000000000000
#define PDPTE_64_IGNORED_2_MASK                                      0x7FF
#define PDPTE_64_IGNORED_2(_)                                        (((_) >> 52) & 0x7FF)

        /**
         * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte region
         * controlled by this entry); otherwise, reserved (must be 0).
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 ExecuteDisable : 1;
#define PDPTE_64_EXECUTE_DISABLE_BIT                                 63
#define PDPTE_64_EXECUTE_DISABLE_FLAG                                0x8000000000000000
#define PDPTE_64_EXECUTE_DISABLE_MASK                                0x01
#define PDPTE_64_EXECUTE_DISABLE(_)                                  (((_) >> 63) & 0x01)
    };

    UINT64 Flags;
} PDPTE_64;

typedef union
{
    struct
    {
        /**
         * [Bit 0] Present; must be 1 to map a 2-MByte page.
         */
        UINT64 Present : 1;
#define PDE_2MB_64_PRESENT_BIT                                       0
#define PDE_2MB_64_PRESENT_FLAG                                      0x01
#define PDE_2MB_64_PRESENT_MASK                                      0x01
#define PDE_2MB_64_PRESENT(_)                                        (((_) >> 0) & 0x01)

        /**
         * [Bit 1] Read/write; if 0, writes may not be allowed to the 2-MByte page referenced by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Write : 1;
#define PDE_2MB_64_WRITE_BIT                                         1
#define PDE_2MB_64_WRITE_FLAG                                        0x02
#define PDE_2MB_64_WRITE_MASK                                        0x01
#define PDE_2MB_64_WRITE(_)                                          (((_) >> 1) & 0x01)

        /**
         * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 2-MByte page referenced by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Supervisor : 1;
#define PDE_2MB_64_SUPERVISOR_BIT                                    2
#define PDE_2MB_64_SUPERVISOR_FLAG                                   0x04
#define PDE_2MB_64_SUPERVISOR_MASK                                   0x01
#define PDE_2MB_64_SUPERVISOR(_)                                     (((_) >> 2) & 0x01)

        /**
         * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the 2-MByte page referenced by
         * this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelWriteThrough : 1;
#define PDE_2MB_64_PAGE_LEVEL_WRITE_THROUGH_BIT                      3
#define PDE_2MB_64_PAGE_LEVEL_WRITE_THROUGH_FLAG                     0x08
#define PDE_2MB_64_PAGE_LEVEL_WRITE_THROUGH_MASK                     0x01
#define PDE_2MB_64_PAGE_LEVEL_WRITE_THROUGH(_)                       (((_) >> 3) & 0x01)

        /**
         * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the 2-MByte page referenced by
         * this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelCacheDisable : 1;
#define PDE_2MB_64_PAGE_LEVEL_CACHE_DISABLE_BIT                      4
#define PDE_2MB_64_PAGE_LEVEL_CACHE_DISABLE_FLAG                     0x10
#define PDE_2MB_64_PAGE_LEVEL_CACHE_DISABLE_MASK                     0x01
#define PDE_2MB_64_PAGE_LEVEL_CACHE_DISABLE(_)                       (((_) >> 4) & 0x01)

        /**
         * [Bit 5] Accessed; indicates whether software has accessed the 2-MByte page referenced by this entry.
         *
         * @see Vol3A[4.8(Accessed and Dirty Flags)]
         */
        UINT64 Accessed : 1;
#define PDE_2MB_64_ACCESSED_BIT                                      5
#define PDE_2MB_64_ACCESSED_FLAG                                     0x20
#define PDE_2MB_64_ACCESSED_MASK                                     0x01
#define PDE_2MB_64_ACCESSED(_)                                       (((_) >> 5) & 0x01)

        /**
         * [Bit 6] Dirty; indicates whether software has written to the 2-MByte page referenced by this entry.
         *
         * @see Vol3A[4.8(Accessed and Dirty Flags)]
         */
        UINT64 Dirty : 1;
#define PDE_2MB_64_DIRTY_BIT                                         6
#define PDE_2MB_64_DIRTY_FLAG                                        0x40
#define PDE_2MB_64_DIRTY_MASK                                        0x01
#define PDE_2MB_64_DIRTY(_)                                          (((_) >> 6) & 0x01)

        /**
         * [Bit 7] Page size; must be 1 (otherwise, this entry references a page directory).
         */
        UINT64 LargePage : 1;
#define PDE_2MB_64_LARGE_PAGE_BIT                                    7
#define PDE_2MB_64_LARGE_PAGE_FLAG                                   0x80
#define PDE_2MB_64_LARGE_PAGE_MASK                                   0x01
#define PDE_2MB_64_LARGE_PAGE(_)                                     (((_) >> 7) & 0x01)

        /**
         * [Bit 8] Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise.
         *
         * @see Vol3A[4.10(Caching Translation Information)]
         */
        UINT64 Global : 1;
#define PDE_2MB_64_GLOBAL_BIT                                        8
#define PDE_2MB_64_GLOBAL_FLAG                                       0x100
#define PDE_2MB_64_GLOBAL_MASK                                       0x01
#define PDE_2MB_64_GLOBAL(_)                                         (((_) >> 8) & 0x01)

        /**
         * [Bits 11:9] Ignored.
         */
        UINT64 Ignored1 : 3;
#define PDE_2MB_64_IGNORED_1_BIT                                     9
#define PDE_2MB_64_IGNORED_1_FLAG                                    0xE00
#define PDE_2MB_64_IGNORED_1_MASK                                    0x07
#define PDE_2MB_64_IGNORED_1(_)                                      (((_) >> 9) & 0x07)

        /**
         * [Bit 12] Indirectly determines the memory type used to access the 2-MByte page referenced by this entry.
         *
         * @note The PAT is supported on all processors that support 4-level paging.
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 Pat : 1;
#define PDE_2MB_64_PAT_BIT                                           12
#define PDE_2MB_64_PAT_FLAG                                          0x1000
#define PDE_2MB_64_PAT_MASK                                          0x01
#define PDE_2MB_64_PAT(_)                                            (((_) >> 12) & 0x01)
        UINT64 Reserved1 : 8;

        /**
         * [Bits 47:21] Physical address of the 2-MByte page referenced by this entry.
         */
        UINT64 PageFrameNumber : 27;
#define PDE_2MB_64_PAGE_FRAME_NUMBER_BIT                             21
#define PDE_2MB_64_PAGE_FRAME_NUMBER_FLAG                            0xFFFFFFE00000
#define PDE_2MB_64_PAGE_FRAME_NUMBER_MASK                            0x7FFFFFF
#define PDE_2MB_64_PAGE_FRAME_NUMBER(_)                              (((_) >> 21) & 0x7FFFFFF)
        UINT64 Reserved2 : 4;

        /**
         * [Bits 58:52] Ignored.
         */
        UINT64 Ignored2 : 7;
#define PDE_2MB_64_IGNORED_2_BIT                                     52
#define PDE_2MB_64_IGNORED_2_FLAG                                    0x7F0000000000000
#define PDE_2MB_64_IGNORED_2_MASK                                    0x7F
#define PDE_2MB_64_IGNORED_2(_)                                      (((_) >> 52) & 0x7F)

        /**
         * [Bits 62:59] Protection key; if CR4.PKE = 1, determines the protection key of the page; ignored otherwise.
         *
         * @see Vol3A[4.6.2(Protection Keys)]
         */
        UINT64 ProtectionKey : 4;
#define PDE_2MB_64_PROTECTION_KEY_BIT                                59
#define PDE_2MB_64_PROTECTION_KEY_FLAG                               0x7800000000000000
#define PDE_2MB_64_PROTECTION_KEY_MASK                               0x0F
#define PDE_2MB_64_PROTECTION_KEY(_)                                 (((_) >> 59) & 0x0F)

        /**
         * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 2-MByte page
         * controlled by this entry); otherwise, reserved (must be 0).
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 ExecuteDisable : 1;
#define PDE_2MB_64_EXECUTE_DISABLE_BIT                               63
#define PDE_2MB_64_EXECUTE_DISABLE_FLAG                              0x8000000000000000
#define PDE_2MB_64_EXECUTE_DISABLE_MASK                              0x01
#define PDE_2MB_64_EXECUTE_DISABLE(_)                                (((_) >> 63) & 0x01)
    };

    UINT64 Flags;
} PDE_2MB_64;

typedef union
{
    struct
    {
        /**
         * [Bit 0] Present; must be 1 to reference a page table.
         */
        UINT64 Present : 1;
#define PDE_64_PRESENT_BIT                                           0
#define PDE_64_PRESENT_FLAG                                          0x01
#define PDE_64_PRESENT_MASK                                          0x01
#define PDE_64_PRESENT(_)                                            (((_) >> 0) & 0x01)

        /**
         * [Bit 1] Read/write; if 0, writes may not be allowed to the 2-MByte region controlled by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Write : 1;
#define PDE_64_WRITE_BIT                                             1
#define PDE_64_WRITE_FLAG                                            0x02
#define PDE_64_WRITE_MASK                                            0x01
#define PDE_64_WRITE(_)                                              (((_) >> 1) & 0x01)

        /**
         * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 2-MByte region controlled by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Supervisor : 1;
#define PDE_64_SUPERVISOR_BIT                                        2
#define PDE_64_SUPERVISOR_FLAG                                       0x04
#define PDE_64_SUPERVISOR_MASK                                       0x01
#define PDE_64_SUPERVISOR(_)                                         (((_) >> 2) & 0x01)

        /**
         * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the page table referenced by this
         * entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelWriteThrough : 1;
#define PDE_64_PAGE_LEVEL_WRITE_THROUGH_BIT                          3
#define PDE_64_PAGE_LEVEL_WRITE_THROUGH_FLAG                         0x08
#define PDE_64_PAGE_LEVEL_WRITE_THROUGH_MASK                         0x01
#define PDE_64_PAGE_LEVEL_WRITE_THROUGH(_)                           (((_) >> 3) & 0x01)

        /**
         * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the page table referenced by this
         * entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelCacheDisable : 1;
#define PDE_64_PAGE_LEVEL_CACHE_DISABLE_BIT                          4
#define PDE_64_PAGE_LEVEL_CACHE_DISABLE_FLAG                         0x10
#define PDE_64_PAGE_LEVEL_CACHE_DISABLE_MASK                         0x01
#define PDE_64_PAGE_LEVEL_CACHE_DISABLE(_)                           (((_) >> 4) & 0x01)

        /**
         * [Bit 5] Accessed; indicates whether this entry has been used for linear-address translation.
         *
         * @see Vol3A[4.8(Accessed and Dirty Flags)]
         */
        UINT64 Accessed : 1;
#define PDE_64_ACCESSED_BIT                                          5
#define PDE_64_ACCESSED_FLAG                                         0x20
#define PDE_64_ACCESSED_MASK                                         0x01
#define PDE_64_ACCESSED(_)                                           (((_) >> 5) & 0x01)
        UINT64 Reserved1 : 1;

        /**
         * [Bit 7] Page size; must be 0 (otherwise, this entry maps a 2-MByte page).
         */
        UINT64 LargePage : 1;
#define PDE_64_LARGE_PAGE_BIT                                        7
#define PDE_64_LARGE_PAGE_FLAG                                       0x80
#define PDE_64_LARGE_PAGE_MASK                                       0x01
#define PDE_64_LARGE_PAGE(_)                                         (((_) >> 7) & 0x01)

        /**
         * [Bits 11:8] Ignored.
         */
        UINT64 Ignored1 : 4;
#define PDE_64_IGNORED_1_BIT                                         8
#define PDE_64_IGNORED_1_FLAG                                        0xF00
#define PDE_64_IGNORED_1_MASK                                        0x0F
#define PDE_64_IGNORED_1(_)                                          (((_) >> 8) & 0x0F)

        /**
         * [Bits 47:12] Physical address of 4-KByte aligned page table referenced by this entry.
         */
        UINT64 PageFrameNumber : 36;
#define PDE_64_PAGE_FRAME_NUMBER_BIT                                 12
#define PDE_64_PAGE_FRAME_NUMBER_FLAG                                0xFFFFFFFFF000
#define PDE_64_PAGE_FRAME_NUMBER_MASK                                0xFFFFFFFFF
#define PDE_64_PAGE_FRAME_NUMBER(_)                                  (((_) >> 12) & 0xFFFFFFFFF)
        UINT64 Reserved2 : 4;

        /**
         * [Bits 62:52] Ignored.
         */
        UINT64 Ignored2 : 11;
#define PDE_64_IGNORED_2_BIT                                         52
#define PDE_64_IGNORED_2_FLAG                                        0x7FF0000000000000
#define PDE_64_IGNORED_2_MASK                                        0x7FF
#define PDE_64_IGNORED_2(_)                                          (((_) >> 52) & 0x7FF)

        /**
         * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 2-MByte region
         * controlled by this entry); otherwise, reserved (must be 0).
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 ExecuteDisable : 1;
#define PDE_64_EXECUTE_DISABLE_BIT                                   63
#define PDE_64_EXECUTE_DISABLE_FLAG                                  0x8000000000000000
#define PDE_64_EXECUTE_DISABLE_MASK                                  0x01
#define PDE_64_EXECUTE_DISABLE(_)                                    (((_) >> 63) & 0x01)
    };

    UINT64 Flags;
} PDE_64;

typedef union
{
    struct
    {
        /**
         * [Bit 0] Present; must be 1 to map a 4-KByte page.
         */
        UINT64 Present : 1;
#define PTE_64_PRESENT_BIT                                           0
#define PTE_64_PRESENT_FLAG                                          0x01
#define PTE_64_PRESENT_MASK                                          0x01
#define PTE_64_PRESENT(_)                                            (((_) >> 0) & 0x01)

        /**
         * [Bit 1] Read/write; if 0, writes may not be allowed to the 4-KByte page referenced by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Write : 1;
#define PTE_64_WRITE_BIT                                             1
#define PTE_64_WRITE_FLAG                                            0x02
#define PTE_64_WRITE_MASK                                            0x01
#define PTE_64_WRITE(_)                                              (((_) >> 1) & 0x01)

        /**
         * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 4-KByte page referenced by this entry.
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 Supervisor : 1;
#define PTE_64_SUPERVISOR_BIT                                        2
#define PTE_64_SUPERVISOR_FLAG                                       0x04
#define PTE_64_SUPERVISOR_MASK                                       0x01
#define PTE_64_SUPERVISOR(_)                                         (((_) >> 2) & 0x01)

        /**
         * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the 4-KByte page referenced by
         * this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelWriteThrough : 1;
#define PTE_64_PAGE_LEVEL_WRITE_THROUGH_BIT                          3
#define PTE_64_PAGE_LEVEL_WRITE_THROUGH_FLAG                         0x08
#define PTE_64_PAGE_LEVEL_WRITE_THROUGH_MASK                         0x01
#define PTE_64_PAGE_LEVEL_WRITE_THROUGH(_)                           (((_) >> 3) & 0x01)

        /**
         * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the 4-KByte page referenced by
         * this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 PageLevelCacheDisable : 1;
#define PTE_64_PAGE_LEVEL_CACHE_DISABLE_BIT                          4
#define PTE_64_PAGE_LEVEL_CACHE_DISABLE_FLAG                         0x10
#define PTE_64_PAGE_LEVEL_CACHE_DISABLE_MASK                         0x01
#define PTE_64_PAGE_LEVEL_CACHE_DISABLE(_)                           (((_) >> 4) & 0x01)

        /**
         * [Bit 5] Accessed; indicates whether software has accessed the 4-KByte page referenced by this entry.
         *
         * @see Vol3A[4.8(Accessed and Dirty Flags)]
         */
        UINT64 Accessed : 1;
#define PTE_64_ACCESSED_BIT                                          5
#define PTE_64_ACCESSED_FLAG                                         0x20
#define PTE_64_ACCESSED_MASK                                         0x01
#define PTE_64_ACCESSED(_)                                           (((_) >> 5) & 0x01)

        /**
         * [Bit 6] Dirty; indicates whether software has written to the 4-KByte page referenced by this entry.
         *
         * @see Vol3A[4.8(Accessed and Dirty Flags)]
         */
        UINT64 Dirty : 1;
#define PTE_64_DIRTY_BIT                                             6
#define PTE_64_DIRTY_FLAG                                            0x40
#define PTE_64_DIRTY_MASK                                            0x01
#define PTE_64_DIRTY(_)                                              (((_) >> 6) & 0x01)

        /**
         * [Bit 7] Indirectly determines the memory type used to access the 4-KByte page referenced by this entry.
         *
         * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
         */
        UINT64 Pat : 1;
#define PTE_64_PAT_BIT                                               7
#define PTE_64_PAT_FLAG                                              0x80
#define PTE_64_PAT_MASK                                              0x01
#define PTE_64_PAT(_)                                                (((_) >> 7) & 0x01)

        /**
         * [Bit 8] Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise.
         *
         * @see Vol3A[4.10(Caching Translation Information)]
         */
        UINT64 Global : 1;
#define PTE_64_GLOBAL_BIT                                            8
#define PTE_64_GLOBAL_FLAG                                           0x100
#define PTE_64_GLOBAL_MASK                                           0x01
#define PTE_64_GLOBAL(_)                                             (((_) >> 8) & 0x01)

        /**
         * [Bits 11:9] Ignored.
         */
        UINT64 CopyOnWrite : 1;
        UINT64 Unused : 1;
        UINT64 Write1 : 1;
#define PTE_64_IGNORED_1_BIT                                         9
#define PTE_64_IGNORED_1_FLAG                                        0xE00
#define PTE_64_IGNORED_1_MASK                                        0x07
#define PTE_64_IGNORED_1(_)                                          (((_) >> 9) & 0x07)

        /**
         * [Bits 47:12] Physical address of the 4-KByte page referenced by this entry.
         */
        UINT64 PageFrameNumber : 36;
#define PTE_64_PAGE_FRAME_NUMBER_BIT                                 12
#define PTE_64_PAGE_FRAME_NUMBER_FLAG                                0xFFFFFFFFF000
#define PTE_64_PAGE_FRAME_NUMBER_MASK                                0xFFFFFFFFF
#define PTE_64_PAGE_FRAME_NUMBER(_)                                  (((_) >> 12) & 0xFFFFFFFFF)
        UINT64 Reserved1 : 4;

        /**
         * [Bits 58:52] Ignored.
         */
        UINT64 Ignored2 : 7;
#define PTE_64_IGNORED_2_BIT                                         52
#define PTE_64_IGNORED_2_FLAG                                        0x7F0000000000000
#define PTE_64_IGNORED_2_MASK                                        0x7F
#define PTE_64_IGNORED_2(_)                                          (((_) >> 52) & 0x7F)

        /**
         * [Bits 62:59] Protection key; if CR4.PKE = 1, determines the protection key of the page; ignored otherwise.
         *
         * @see Vol3A[4.6.2(Protection Keys)]
         */
        UINT64 ProtectionKey : 4;
#define PTE_64_PROTECTION_KEY_BIT                                    59
#define PTE_64_PROTECTION_KEY_FLAG                                   0x7800000000000000
#define PTE_64_PROTECTION_KEY_MASK                                   0x0F
#define PTE_64_PROTECTION_KEY(_)                                     (((_) >> 59) & 0x0F)

        /**
         * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte page
         * controlled by this entry); otherwise, reserved (must be 0).
         *
         * @see Vol3A[4.6(Access Rights)]
         */
        UINT64 ExecuteDisable : 1;
#define PTE_64_EXECUTE_DISABLE_BIT                                   63
#define PTE_64_EXECUTE_DISABLE_FLAG                                  0x8000000000000000
#define PTE_64_EXECUTE_DISABLE_MASK                                  0x01
#define PTE_64_EXECUTE_DISABLE(_)                                    (((_) >> 63) & 0x01)
    };

    UINT64 Flags;
} PTE_64;

#endif