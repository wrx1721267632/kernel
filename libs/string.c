/*************************************************************************
	> File Name: libs/string.c
	> Author:
	> Mail:
	> Created Time: 2016年10月27日 星期四 21时52分36秒
 ************************************************************************/

#include"string.h"

inline void *memcpy(void *dest, const void *src, uint32_t len)
{
    uint8_t *str1 = dest;
    const uint8_t *str2 = src;

    if (src == NULL || dest == NULL)
    {
        return dest;
    }

    for ( ; len != 0; len--)
    {
        *str1++ = *str2++;
    }

    return dest;
}

inline void *memset(void *dest, uint8_t val, uint32_t len)
{
    uint8_t *dst = (uint8_t *)dest;

    if (dest == NULL)
    {
        return dest;
    }

    for(; len != 0; len--)
    {
        *dst++ = val;
    }

    return dest;
}

inline void bzero(void *dest, uint32_t len)
{
    memset(dest, 0, len);
}

inline int strcmp(const int8_t *str1, const int8_t *str2)
{
    const int8_t *s1 = str1;
    const int8_t *s2 = str2;

    int8_t c1, c2;

    do {
        c1 = *s1++;
        c2 = *s2++;

        if (c1 == '\0') {
            return c1 - c2;
        }
    } while (c1 == c2);

    return c1 - c2;
}

int8_t* strcpy(int8_t *dest, const int8_t *val)
{
    int8_t *dst = dest;
    const int8_t *str = val;

    if (dest == NULL || val == NULL)
    {
        return dest;
    }

    while ( (*dst++ = *str++) != '\0')
        ;

    return dest;
}

int8_t* strcat(int8_t* dest, const int8_t* val)
{
    int8_t * dst = dest;
    const int8_t * str = val;

    if (dst == NULL || str == NULL)
    {
        return dest;
    }

    for ( ; *dst++ != '\0'; )
        ;

    do {
        *dst++ = *str;
    } while (*str++ != '\0');

    return dest;
}

int strlen(const int8_t* src)
{
    int number;

    number = 0;

    while (*src++ != '\0')
    {
        number++;
    }

    return number;
}

char *strncpy(char* dest, const char *src, uint32_t len)
{
    char *dst = dest;

    while (len > 0) {
        while (*src) {
            *dest++ = *src++;
        }
        len--;
    }
    *dest = '\0';

    return dst;
}
