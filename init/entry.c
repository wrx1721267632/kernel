/*************************************************************************
    > File Name: entry.c
    > Author: ma6174
    > Mail: ma6174@163.com
    > Created Time: 2016年10月23日 星期日 22时53分17秒
 ************************************************************************/

#include "../include/console.h"
#include "../include/debug.h"

int kern_entry()
{
    init_debug();

    //清屏
    console_clear();

    //输出字符串
    console_write_color("hello, kernel\n", rc_black, rc_green);

    panic("test");

    return 0;
}
