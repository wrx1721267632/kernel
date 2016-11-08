/*************************************************************************
    > File Name: entry.c
    > Author: ma6174
    > Mail: ma6174@163.com
    > Created Time: 2016年10月23日 星期日 22时53分17秒
 ************************************************************************/

#include "debug.h"
#include "gdt.h"
#include "console.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"

int kern_entry()
{
    init_debug();
    init_gdt();
    init_idt();

    //清屏
    console_clear();

    //
    print_cur_status();

    //输出字符串
    console_write_color("hello, kernel\n", rc_black, rc_green);

    init_timer(200);

    //开启中断
    //asm volatile ("sti");

    printk("kernel in memory start: 0x%x\n", kern_start);
    printk("kernel in memory end: 0x%x\n", kern_end);
    printk("kernel in memory used: %d KB\n\n", (kern_end - kern_start +
                1023) / 1024);

    show_memory_map();

    init_pmm();

    printk("\nThe count of Physical Memory Page is: %u\n\n", phy_page_count);
    uint32_t allc_addr = NULL;
    printk("Test Physical Memory Alloc: \n");
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical addr: 0x%x\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical addr: 0x%x\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical addr: 0x%x\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical addr: 0x%x\n", allc_addr);

    return 0;
}
