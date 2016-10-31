/*************************************************************************
	> File Name: include/debug.h
	> Author:
	> Mail:
	> Created Time: 2016年10月27日 星期四 23时03分27秒
 ************************************************************************/

#ifndef _INCLUDE_DEBUG_H
#define _INCLUDE_DEBUG_H

#include"console.h"
#include"vargs.h"
#include"elf.h"

#define assert(x, info)         \
        do {                    \
            if ((!x)) {         \
                panic(info);    \
            }                   \
        } while(0)

//编译器间静态检测
#define static_assert(x)        \
        switch (x) { case 0: case(x): ; }

//初始化Debug信息
void init_debug();

//打印当前的函数调用栈信息
void panic(const char *msg);

//打印当前的段存储器
void print_cur_status();

//内核打印函数
void printk(const char *format, ...);

//内核打印函数带颜色
void printk_color(real_color_t back, real_color_t fore, const char *format, ...);

#endif
