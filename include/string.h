/*************************************************************************
	> File Name: include/string.h
	> Author:
	> Mail:
	> Created Time: 2016年10月27日 星期四 16时52分33秒
 ************************************************************************/

#ifndef _INCLUDE_STRING_H
#define _INCLUDE_STRING_H

#include"types.h"

void *memcpy(void *dest, const void *src, uint32_t len);

void *memset(void *dest, uint8_t val, uint32_t len);

void bzero(void *dest, uint32_t len);

int strcmp(const int8_t *str1, const int8_t *str2);

int8_t *strcpy(int8_t *dest, const int8_t *src);

int8_t *strcat(int8_t *dest, const int8_t *src);

int strlen(const int8_t *dest);

char *strncpy(char *dest, const char *src, uint32_t len);

#endif
