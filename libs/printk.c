/*************************************************************************
	> File Name: printk.c
	> Author:
	> Mail:
	> Created Time: 2016年10月30日 星期日 11时24分42秒
 ************************************************************************/

#include"../include/vargs.h"
#include"../include/string.h"
#include"../include/common.h"

static void printchar(int8_t str);
static int  vprintk(const int8_t * format, char *ap);
static void printi(int number);
static void prints(char *s);
static void printx(int number);

void printx(int number)
{
    char *hex = "0123456789ABCDEF";
    int value;
    int i = 7;

    while (i >= 0)
    {
        value = number >> i*4;
        console_putc_color(hex[value & 0xF], rc_black, rc_red);
        i--;
    }
}

void prints(char *s)
{
    console_write_color(s, rc_black, rc_red);
}

void printchar(int8_t str)
{
    console_putc_color(str, rc_black, rc_red);
}

void printi(int number)
{
    char s[32];
    int sign;
    int i = 0;
    sign = number;

    if (sign < 0)
    {
        number = -number;
    }

    do {
        s[i++] = number % 10 + '0';
    } while ((number /= 10) > 0);

    if (sign < 0)
    {
        s[i++] = '-';
    }

    i--;
    for ( ; i>= 0; i--)
    {
        console_putc_color(s[i], rc_black, rc_red);
    }
}

int printk(const int8_t * format, ...)
{
    int number;
    char *arg;
    va_start(arg, format);
    number = vprintk(format, arg);
    va_end(arg);
    return number;
}

int vprintk(const int8_t * format, char *ap)
{
    int pc;
    pc = 0;

    for ( ; *format != '0'; ++format)
    {
        if (*format == '%') {
            ++format;
            if ((*format) == 'c') {
                printchar(va_arg(ap, int));
                pc++;
            } else if (*format == 'd') {
                printi(va_arg(ap, int));
                pc++;
            } else if (*format == 's') {
                prints(va_arg(ap, char*));
                pc++;
            } else if (*format == 'x') {
                printx((va_arg(ap, int)));
                pc++;
            } else{
                printchar(*format);
                pc++;
            }
        } else {
            printchar(*format);
        }
    }

    return pc;
}
