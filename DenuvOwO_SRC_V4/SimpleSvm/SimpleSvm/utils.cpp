#include "utils.h"

namespace Utils
{
    void* PfnToVirtualAddr(uintptr_t pfn)
    {
        PHYSICAL_ADDRESS pa;

        pa.QuadPart = pfn << PAGE_SHIFT;

        return MmGetVirtualForPhysical(pa);
    }

    PFN_NUMBER VirtualAddrToPfn(uintptr_t va)
    {
        return MmGetPhysicalAddress((void*)va).QuadPart >> PAGE_SHIFT;
    }


    PT_ENTRY_64* GetPte(void* virtual_address, uintptr_t pml4_base_pa, int (*page_table_callback)(PT_ENTRY_64*, void*), void* callback_data)
    {
        AddressTranslationHelper helper;

        helper.as_int64 = (uintptr_t)virtual_address;

        PHYSICAL_ADDRESS pml4_physical;
        pml4_physical.QuadPart = pml4_base_pa;

        PML4E_64* pml4;
        PML4E_64* pml4e;

        pml4 = (PML4E_64*)MmGetVirtualForPhysical(pml4_physical);


        if (pml4 == NULL)
        {
            return NULL;
        }

        pml4e = &pml4[helper.AsIndex.pml4];

        if (page_table_callback)
        {
            page_table_callback((PT_ENTRY_64*)pml4e, callback_data);
        }
        if (pml4e->Present == FALSE)
        {
            return NULL;
        }

        PDPTE_64* pdpt;
        PDPTE_64* pdpte;

        pdpt = (PDPTE_64*)Utils::PfnToVirtualAddr(pml4e->PageFrameNumber);

        if (pdpt == NULL)
        {
            return NULL;
        }

        pdpte = &pdpt[helper.AsIndex.pdpt];

        if (page_table_callback)
        {
            page_table_callback((PT_ENTRY_64*)pdpte, callback_data);
        }

        if ((pdpte->LargePage == TRUE))
        {
            return (PT_ENTRY_64*)pdpte;
        }
        else if (pdpte->Present == FALSE)
        {
            return NULL;
        }

        PDE_64* pd;
        PDE_64* pde;

        pd = (PDE_64*)Utils::PfnToVirtualAddr(pdpte->PageFrameNumber);

        if (pd == NULL)
        {
            return NULL;
        }

        pde = &pd[helper.AsIndex.pd];

        if (page_table_callback)
        {
            page_table_callback((PT_ENTRY_64*)pde, callback_data);
        }

        if (pde->LargePage == TRUE)
        {
            return (PT_ENTRY_64*)pde;
        }
        else if (pde->Present == FALSE)
        {
            return NULL;
        }

        PTE_64* pt;
        PTE_64* pte;

        pt = (PTE_64*)Utils::PfnToVirtualAddr(pde->PageFrameNumber);

        if (pt == NULL)
        {
            return NULL;
        }

        pte = &pt[helper.AsIndex.pt];

        if (page_table_callback)
        {
            page_table_callback((PT_ENTRY_64*)pte, callback_data);
        }

        if (pte->Present == FALSE)
        {
            return NULL;
        }

        return  (PT_ENTRY_64*)pte;
    }
    

    uintptr_t FindPattern(uintptr_t region_base, size_t region_size, const char* pattern, size_t pattern_size, char wildcard)
    {
        for (auto byte = (char*)region_base; byte < (char*)region_base + region_size;
            ++byte)
        {
            bool found = true;

            for (char* pattern_byte = (char*)pattern, *begin = byte; pattern_byte < pattern + pattern_size; ++pattern_byte, ++begin)
            {
                if (*pattern_byte != *begin && *pattern_byte != wildcard)
                {
                    found = false;
                }
            }

            if (found)
            {
                return (uintptr_t)byte;
            }
        }

        return 0;
    }



    int Exponent(int base, int power)
    {
        int start = 1;
        for (int i = 0; i < power; ++i)
        {
            start *= base;
        }

        return start;
    }
}