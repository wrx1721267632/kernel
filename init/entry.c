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
    asm volatile ("sti");
    return 0;
}
