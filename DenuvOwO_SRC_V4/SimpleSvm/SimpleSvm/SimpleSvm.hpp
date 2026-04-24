/*!
    @file       SimpleSvm.hpp

    @brief      SVM specific definitions.

    @author     Satoshi Tanda

    @copyright  Copyright (c) 2017-2019, Satoshi Tanda. All rights reserved.
 */
#pragma once

#include <basetsd.h>

union AddressTranslationHelper
{
    // Indexes to locate paging-structure entries corresponds to this virtual
    // address.
    //
    struct
    {
        UINT64 page_offset : 12;  //< [11:0]
        UINT64 pt : 9;            //< [20:12]
        UINT64 pd : 9;            //< [29:21]
        UINT64 pdpt : 9;          //< [38:30]
        UINT64 pml4 : 9;          //< [47:39]
    } AsIndex;

    UINT64 as_int64;
};

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
    } Fields;

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
    } Fields;

    UINT64 Flags;
} PDPTE_64;

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
    } Fields;

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
    } Fields;

    UINT64 Flags;
} PTE_64;

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
    } Fields;

    UINT64 Flags;
} PT_ENTRY_64;

//
// A size of two the MSR permissions map.
//
#define SVM_MSR_PERMISSIONS_MAP_SIZE    (PAGE_SIZE * 2)

//
// See "SVM Related MSRs"
//
#define SVM_MSR_VM_CR                   0xc0010114
#define SVM_MSR_VM_HSAVE_PA             0xc0010117

#define SVM_VM_CR_SVMDIS                (1UL << 4)

//
// See "VMCB Layout, Control Area"
//
#define SVM_INTERCEPT_MISC1_CPUID       (1UL << 18)
#define SVM_INTERCEPT_MISC1_MSR_PROT    (1UL << 28)
#define SVM_INTERCEPT_MISC2_VMRUN       (1UL << 0)
#define SVM_NP_ENABLE_NP_ENABLE         (1UL << 0)

typedef struct _VMCB_CONTROL_AREA
{
    UINT16 InterceptCrRead;             // +0x000
    UINT16 InterceptCrWrite;            // +0x002
    UINT16 InterceptDrRead;             // +0x004
    UINT16 InterceptDrWrite;            // +0x006
    UINT32 InterceptException;          // +0x008
    UINT32 InterceptMisc1;              // +0x00c
    UINT32 InterceptMisc2;              // +0x010
    UINT8 Reserved1[0x03c - 0x014];     // +0x014
    UINT16 PauseFilterThreshold;        // +0x03c
    UINT16 PauseFilterCount;            // +0x03e
    UINT64 IopmBasePa;                  // +0x040
    UINT64 MsrpmBasePa;                 // +0x048
    UINT64 TscOffset;                   // +0x050
    UINT32 GuestAsid;                   // +0x058
    UINT32 TlbControl;                  // +0x05c
    UINT64 VIntr;                       // +0x060
    UINT64 InterruptShadow;             // +0x068
    UINT64 ExitCode;                    // +0x070
    UINT64 ExitInfo1;                   // +0x078
    UINT64 ExitInfo2;                   // +0x080
    UINT64 ExitIntInfo;                 // +0x088
    UINT64 NpEnable;                    // +0x090
    UINT64 AvicApicBar;                 // +0x098
    UINT64 GuestPaOfGhcb;               // +0x0a0
    UINT64 EventInj;                    // +0x0a8
    UINT64 NCr3;                        // +0x0b0
    UINT64 LbrVirtualizationEnable;     // +0x0b8
    UINT64 VmcbClean;                   // +0x0c0
    UINT64 NRip;                        // +0x0c8
    UINT8 NumOfBytesFetched;            // +0x0d0
    UINT8 GuestInstructionBytes[15];    // +0x0d1
    UINT64 AvicApicBackingPagePointer;  // +0x0e0
    UINT64 Reserved2;                   // +0x0e8
    UINT64 AvicLogicalTablePointer;     // +0x0f0
    UINT64 AvicPhysicalTablePointer;    // +0x0f8
    UINT64 Reserved3;                   // +0x100
    UINT64 VmcbSaveStatePointer;        // +0x108
    UINT8 Reserved4[0x400 - 0x110];     // +0x110
} VMCB_CONTROL_AREA, *PVMCB_CONTROL_AREA;
static_assert(sizeof(VMCB_CONTROL_AREA) == 0x400,
              "VMCB_CONTROL_AREA Size Mismatch");

//
// See "VMCB Layout, State Save Area"
//
typedef struct _VMCB_STATE_SAVE_AREA
{
    UINT16 EsSelector;                  // +0x000
    UINT16 EsAttrib;                    // +0x002
    UINT32 EsLimit;                     // +0x004
    UINT64 EsBase;                      // +0x008
    UINT16 CsSelector;                  // +0x010
    UINT16 CsAttrib;                    // +0x012
    UINT32 CsLimit;                     // +0x014
    UINT64 CsBase;                      // +0x018
    UINT16 SsSelector;                  // +0x020
    UINT16 SsAttrib;                    // +0x022
    UINT32 SsLimit;                     // +0x024
    UINT64 SsBase;                      // +0x028
    UINT16 DsSelector;                  // +0x030
    UINT16 DsAttrib;                    // +0x032
    UINT32 DsLimit;                     // +0x034
    UINT64 DsBase;                      // +0x038
    UINT16 FsSelector;                  // +0x040
    UINT16 FsAttrib;                    // +0x042
    UINT32 FsLimit;                     // +0x044
    UINT64 FsBase;                      // +0x048
    UINT16 GsSelector;                  // +0x050
    UINT16 GsAttrib;                    // +0x052
    UINT32 GsLimit;                     // +0x054
    UINT64 GsBase;                      // +0x058
    UINT16 GdtrSelector;                // +0x060
    UINT16 GdtrAttrib;                  // +0x062
    UINT32 GdtrLimit;                   // +0x064
    UINT64 GdtrBase;                    // +0x068
    UINT16 LdtrSelector;                // +0x070
    UINT16 LdtrAttrib;                  // +0x072
    UINT32 LdtrLimit;                   // +0x074
    UINT64 LdtrBase;                    // +0x078
    UINT16 IdtrSelector;                // +0x080
    UINT16 IdtrAttrib;                  // +0x082
    UINT32 IdtrLimit;                   // +0x084
    UINT64 IdtrBase;                    // +0x088
    UINT16 TrSelector;                  // +0x090
    UINT16 TrAttrib;                    // +0x092
    UINT32 TrLimit;                     // +0x094
    UINT64 TrBase;                      // +0x098
    UINT8 Reserved1[0x0cb - 0x0a0];     // +0x0a0
    UINT8 Cpl;                          // +0x0cb
    UINT32 Reserved2;                   // +0x0cc
    UINT64 Efer;                        // +0x0d0
    UINT8 Reserved3[0x148 - 0x0d8];     // +0x0d8
    UINT64 Cr4;                         // +0x148
    UINT64 Cr3;                         // +0x150
    UINT64 Cr0;                         // +0x158
    UINT64 Dr7;                         // +0x160
    UINT64 Dr6;                         // +0x168
    UINT64 Rflags;                      // +0x170
    UINT64 Rip;                         // +0x178
    UINT8 Reserved4[0x1d8 - 0x180];     // +0x180
    UINT64 Rsp;                         // +0x1d8
    UINT8 Reserved5[0x1f8 - 0x1e0];     // +0x1e0
    UINT64 Rax;                         // +0x1f8
    UINT64 Star;                        // +0x200
    UINT64 LStar;                       // +0x208
    UINT64 CStar;                       // +0x210
    UINT64 SfMask;                      // +0x218
    UINT64 KernelGsBase;                // +0x220
    UINT64 SysenterCs;                  // +0x228
    UINT64 SysenterEsp;                 // +0x230
    UINT64 SysenterEip;                 // +0x238
    UINT64 Cr2;                         // +0x240
    UINT8 Reserved6[0x268 - 0x248];     // +0x248
    UINT64 GPat;                        // +0x268
    UINT64 DbgCtl;                      // +0x270
    UINT64 BrFrom;                      // +0x278
    UINT64 BrTo;                        // +0x280
    UINT64 LastExcepFrom;               // +0x288
    UINT64 LastExcepTo;                 // +0x290
} VMCB_STATE_SAVE_AREA, *PVMCB_STATE_SAVE_AREA;
static_assert(sizeof(VMCB_STATE_SAVE_AREA) == 0x298,
              "VMCB_STATE_SAVE_AREA Size Mismatch");

//
// An entire VMCB (Virtual machine control block) layout.
//
typedef struct _VMCB
{
    VMCB_CONTROL_AREA ControlArea;
    VMCB_STATE_SAVE_AREA StateSaveArea;
    UINT8 Reserved1[0x1000 - sizeof(VMCB_CONTROL_AREA) - sizeof(VMCB_STATE_SAVE_AREA)];
} VMCB, *PVMCB;
static_assert(sizeof(VMCB) == 0x1000,
              "VMCB Size Mismatch");

//
// See "Event Injection"
//
typedef struct _EVENTINJ
{
    union
    {
        UINT64 AsUInt64;
        struct
        {
            UINT64 Vector : 8;          // [0:7]
            UINT64 Type : 3;            // [8:10]
            UINT64 ErrorCodeValid : 1;  // [11]
            UINT64 Reserved1 : 19;      // [12:30]
            UINT64 Valid : 1;           // [31]
            UINT64 ErrorCode : 32;      // [32:63]
        } Fields;
    };
} EVENTINJ, *PEVENTINJ;
static_assert(sizeof(EVENTINJ) == 8,
              "EVENTINJ Size Mismatch");

//
// See "SVM Intercept Codes"
//
#define VMEXIT_CR0_READ             0x0000
#define VMEXIT_CR1_READ             0x0001
#define VMEXIT_CR2_READ             0x0002
#define VMEXIT_CR3_READ             0x0003
#define VMEXIT_CR4_READ             0x0004
#define VMEXIT_CR5_READ             0x0005
#define VMEXIT_CR6_READ             0x0006
#define VMEXIT_CR7_READ             0x0007
#define VMEXIT_CR8_READ             0x0008
#define VMEXIT_CR9_READ             0x0009
#define VMEXIT_CR10_READ            0x000a
#define VMEXIT_CR11_READ            0x000b
#define VMEXIT_CR12_READ            0x000c
#define VMEXIT_CR13_READ            0x000d
#define VMEXIT_CR14_READ            0x000e
#define VMEXIT_CR15_READ            0x000f
#define VMEXIT_CR0_WRITE            0x0010
#define VMEXIT_CR1_WRITE            0x0011
#define VMEXIT_CR2_WRITE            0x0012
#define VMEXIT_CR3_WRITE            0x0013
#define VMEXIT_CR4_WRITE            0x0014
#define VMEXIT_CR5_WRITE            0x0015
#define VMEXIT_CR6_WRITE            0x0016
#define VMEXIT_CR7_WRITE            0x0017
#define VMEXIT_CR8_WRITE            0x0018
#define VMEXIT_CR9_WRITE            0x0019
#define VMEXIT_CR10_WRITE           0x001a
#define VMEXIT_CR11_WRITE           0x001b
#define VMEXIT_CR12_WRITE           0x001c
#define VMEXIT_CR13_WRITE           0x001d
#define VMEXIT_CR14_WRITE           0x001e
#define VMEXIT_CR15_WRITE           0x001f
#define VMEXIT_DR0_READ             0x0020
#define VMEXIT_DR1_READ             0x0021
#define VMEXIT_DR2_READ             0x0022
#define VMEXIT_DR3_READ             0x0023
#define VMEXIT_DR4_READ             0x0024
#define VMEXIT_DR5_READ             0x0025
#define VMEXIT_DR6_READ             0x0026
#define VMEXIT_DR7_READ             0x0027
#define VMEXIT_DR8_READ             0x0028
#define VMEXIT_DR9_READ             0x0029
#define VMEXIT_DR10_READ            0x002a
#define VMEXIT_DR11_READ            0x002b
#define VMEXIT_DR12_READ            0x002c
#define VMEXIT_DR13_READ            0x002d
#define VMEXIT_DR14_READ            0x002e
#define VMEXIT_DR15_READ            0x002f
#define VMEXIT_DR0_WRITE            0x0030
#define VMEXIT_DR1_WRITE            0x0031
#define VMEXIT_DR2_WRITE            0x0032
#define VMEXIT_DR3_WRITE            0x0033
#define VMEXIT_DR4_WRITE            0x0034
#define VMEXIT_DR5_WRITE            0x0035
#define VMEXIT_DR6_WRITE            0x0036
#define VMEXIT_DR7_WRITE            0x0037
#define VMEXIT_DR8_WRITE            0x0038
#define VMEXIT_DR9_WRITE            0x0039
#define VMEXIT_DR10_WRITE           0x003a
#define VMEXIT_DR11_WRITE           0x003b
#define VMEXIT_DR12_WRITE           0x003c
#define VMEXIT_DR13_WRITE           0x003d
#define VMEXIT_DR14_WRITE           0x003e
#define VMEXIT_DR15_WRITE           0x003f
#define VMEXIT_EXCEPTION_DE         0x0040
#define VMEXIT_EXCEPTION_DB         0x0041
#define VMEXIT_EXCEPTION_NMI        0x0042
#define VMEXIT_EXCEPTION_BP         0x0043
#define VMEXIT_EXCEPTION_OF         0x0044
#define VMEXIT_EXCEPTION_BR         0x0045
#define VMEXIT_EXCEPTION_UD         0x0046
#define VMEXIT_EXCEPTION_NM         0x0047
#define VMEXIT_EXCEPTION_DF         0x0048
#define VMEXIT_EXCEPTION_09         0x0049
#define VMEXIT_EXCEPTION_TS         0x004a
#define VMEXIT_EXCEPTION_NP         0x004b
#define VMEXIT_EXCEPTION_SS         0x004c
#define VMEXIT_EXCEPTION_GP         0x004d
#define VMEXIT_EXCEPTION_PF         0x004e
#define VMEXIT_EXCEPTION_15         0x004f
#define VMEXIT_EXCEPTION_MF         0x0050
#define VMEXIT_EXCEPTION_AC         0x0051
#define VMEXIT_EXCEPTION_MC         0x0052
#define VMEXIT_EXCEPTION_XF         0x0053
#define VMEXIT_EXCEPTION_20         0x0054
#define VMEXIT_EXCEPTION_21         0x0055
#define VMEXIT_EXCEPTION_22         0x0056
#define VMEXIT_EXCEPTION_23         0x0057
#define VMEXIT_EXCEPTION_24         0x0058
#define VMEXIT_EXCEPTION_25         0x0059
#define VMEXIT_EXCEPTION_26         0x005a
#define VMEXIT_EXCEPTION_27         0x005b
#define VMEXIT_EXCEPTION_28         0x005c
#define VMEXIT_EXCEPTION_VC         0x005d
#define VMEXIT_EXCEPTION_SX         0x005e
#define VMEXIT_EXCEPTION_31         0x005f
#define VMEXIT_INTR                 0x0060
#define VMEXIT_NMI                  0x0061
#define VMEXIT_SMI                  0x0062
#define VMEXIT_INIT                 0x0063
#define VMEXIT_VINTR                0x0064
#define VMEXIT_CR0_SEL_WRITE        0x0065
#define VMEXIT_IDTR_READ            0x0066
#define VMEXIT_GDTR_READ            0x0067
#define VMEXIT_LDTR_READ            0x0068
#define VMEXIT_TR_READ              0x0069
#define VMEXIT_IDTR_WRITE           0x006a
#define VMEXIT_GDTR_WRITE           0x006b
#define VMEXIT_LDTR_WRITE           0x006c
#define VMEXIT_TR_WRITE             0x006d
#define VMEXIT_RDTSC                0x006e
#define VMEXIT_RDPMC                0x006f
#define VMEXIT_PUSHF                0x0070
#define VMEXIT_POPF                 0x0071
#define VMEXIT_CPUID                0x0072
#define VMEXIT_RSM                  0x0073
#define VMEXIT_IRET                 0x0074
#define VMEXIT_SWINT                0x0075
#define VMEXIT_INVD                 0x0076
#define VMEXIT_PAUSE                0x0077
#define VMEXIT_HLT                  0x0078
#define VMEXIT_INVLPG               0x0079
#define VMEXIT_INVLPGA              0x007a
#define VMEXIT_IOIO                 0x007b
#define VMEXIT_MSR                  0x007c
#define VMEXIT_TASK_SWITCH          0x007d
#define VMEXIT_FERR_FREEZE          0x007e
#define VMEXIT_SHUTDOWN             0x007f
#define VMEXIT_VMRUN                0x0080
#define VMEXIT_VMMCALL              0x0081
#define VMEXIT_VMLOAD               0x0082
#define VMEXIT_VMSAVE               0x0083
#define VMEXIT_STGI                 0x0084
#define VMEXIT_CLGI                 0x0085
#define VMEXIT_SKINIT               0x0086
#define VMEXIT_RDTSCP               0x0087
#define VMEXIT_ICEBP                0x0088
#define VMEXIT_WBINVD               0x0089
#define VMEXIT_MONITOR              0x008a
#define VMEXIT_MWAIT                0x008b
#define VMEXIT_MWAIT_CONDITIONAL    0x008c
#define VMEXIT_XSETBV               0x008d
#define VMEXIT_EFER_WRITE_TRAP      0x008f
#define VMEXIT_CR0_WRITE_TRAP       0x0090
#define VMEXIT_CR1_WRITE_TRAP       0x0091
#define VMEXIT_CR2_WRITE_TRAP       0x0092
#define VMEXIT_CR3_WRITE_TRAP       0x0093
#define VMEXIT_CR4_WRITE_TRAP       0x0094
#define VMEXIT_CR5_WRITE_TRAP       0x0095
#define VMEXIT_CR6_WRITE_TRAP       0x0096
#define VMEXIT_CR7_WRITE_TRAP       0x0097
#define VMEXIT_CR8_WRITE_TRAP       0x0098
#define VMEXIT_CR9_WRITE_TRAP       0x0099
#define VMEXIT_CR10_WRITE_TRAP      0x009a
#define VMEXIT_CR11_WRITE_TRAP      0x009b
#define VMEXIT_CR12_WRITE_TRAP      0x009c
#define VMEXIT_CR13_WRITE_TRAP      0x009d
#define VMEXIT_CR14_WRITE_TRAP      0x009e
#define VMEXIT_CR15_WRITE_TRAP      0x009f
#define VMEXIT_NPF                  0x0400
#define AVIC_INCOMPLETE_IPI         0x0401
#define AVIC_NOACCEL                0x0402
#define VMEXIT_VMGEXIT              0x0403
#define VMEXIT_INVALID              -1
