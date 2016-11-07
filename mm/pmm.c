/*************************************************************************
	> File Name: mm/pmm.c
	> Author:
	> Mail:
	> Created Time: 2016年11月07日 星期一 18时54分50秒
 ************************************************************************/

#include "multiboot.h"
#include "common.h"
#include "debug.h"
#include "pmm.h"

void show_memory_map()
{
    uint32_t mmap_addr   = glb_mboot_ptr->mmap_addr;
    uint32_t mmap_length = glb_mboot_ptr->mmap_length;

    printk("Memory map:\n");

    mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
    for (mmap = (mmap_entry_t *)mmap_addr; (uint32_t)mmap <
            mmap_addr + mmap_length; mmap++) {
        printk("base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
                (uint32_t)mmap->base_addr_high, (uint32_t)mmap->base_addr_low,
                (uint32_t)mmap->length_high, (uint32_t)mmap->length_low,
                (uint32_t)mmap->type);
    }
}


