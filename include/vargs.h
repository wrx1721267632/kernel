/*************************************************************************
	> File Name: include/vargs.h
	> Author:
	> Mail:
	> Created Time: 2016年10月27日 星期四 23时06分31秒
 ************************************************************************/

#ifndef _INCLUDE_VARGS_H
#define _INCLUDE_VARGS_H

#include"console.h"

typedef __builtin_va_list va_list;

//(p = (va_list)&first + sizeof(first))
#define va_start(ap, last) (__builtin_va_start(ap, last))
//( *(next) ( (p += sizeof(next)) - sizeof(next) ) )
#define va_arg(ap, type) (__builtin_va_arg(ap, type))
//(p = (va_list)NULL)
#define va_end(ap)

#endif
