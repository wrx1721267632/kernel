/*************************************************************************
    > File Name: libs/commom.c
    > Author: ma6174
    > Mail: ma6174@163.com
    > Created Time: 2016年10月25日 星期二 19时59分14秒
 ************************************************************************/

#include "../include/common.h"

//端口写一个字节
inline void outb(uint16_t port, uint8_t value)
{
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

//端口读一个字节
inline uint8_t inb(uint16_t port)
{
    uint8_t ret;

    asm volatile("inb %1, %0" : "=a" (ret): "dN" (port));

    return ret;
}

//端口读入一个字
inline uint16_t inw(uint16_t port)
{
    uint16_t ret;

    asm volatile("inw %1, %0" : "=a" (ret): "dN" (port));

    return ret;
}
