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

//内核打印函数
void printk(const char *format, ...);

//内核打印函数带颜色
void printk(real_color_t back, real_color_t fore, const char *format, ...);

#endif
