/*************************************************************************
	> File Name: include/common.h
	> Author:
	> Mail:
	> Created Time: 2016年10月25日 星期二 20时38分07秒
 ************************************************************************/

#ifndef _INCLUDE_COMMON_H
#define _INCLUDE_COMMON_H

#include"types.h"

//端口写一个字节
void outb(uint16_t port, uint8_t value);

//端口读一个字节
uint8_t inb(uint16_t port);

//端口读一个字
uint16_t inw(uint16_t port);

#endif
