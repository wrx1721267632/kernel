/*************************************************************************
	> File Name: drivers/console.c
	> Author:
	> Mail:
	> Created Time: 2016年10月25日 星期二 22时15分21秒
 ************************************************************************/

#include "console.h"
#include "common.h"

//VGA的显示缓冲的起点是0xb8000
static uint16_t *video_memory = (uint16_t *)0xB8000;

//屏幕光标的坐标
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//将光标设置为(cursor_x,cursor_y)的坐标处
static void move_cursor()
{
    //获得屏幕相对的一维坐标的下标,屏幕宽80
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;

    //向0x3D4发送14,表示我们即将将光标的高字节发送往0x3D5
    //向0x3D4发送15,表示我们即将将光标的低字节发送往0x3D5

    outb(0x3D4, 14);                        //告诉VGA我们要设置光标的高字节
    outb(0x3D5, cursorLocation >> 8);       //发送高8位
    outb(0x3D4, 15);                        //告诉VGA我们要设置光标的低字节
    outb(0x3D5, cursorLocation);            //发送低八位
}

//清屏操作
void console_clear()
{
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);

    int i;
    for (i = 0; i < 80 * 25; i++)
    {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

//屏幕滚动操作
static void scroll()
{
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);

    //cursor_y >= 25时就该换行了
    if (cursor_y >= 25) {
        int i;

        for (i = 0; i < 24 * 80; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        for (i = 24 * 80; i < 25 * 80; i++)
        {
            video_memory[i] = blank;
        }

        cursor_y = 24;
    }
}

//显示指定颜色的字符
void console_putc_color(char c, real_color_t back, real_color_t fore)
{
    uint8_t back_color = (uint8_t) back;
    uint8_t fore_color = (uint8_t) fore;

    uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
    uint16_t attribute = attribute_byte << 8;

    //0x08是退格键的ASCII, 0x09是tab键的ASCII码
    if (c == 0x08 && cursor_x) {
        cursor_x--;
    } else if (c == 0x09) {
        cursor_x = (cursor_x + 8) & ~(8-1);
    } else if (c =='\r') {
        cursor_x = 0;
    } else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c >= ' ') {
        video_memory[cursor_y * 80 + cursor_x] = c | attribute;
        cursor_x ++;
    }

    //每80行字符一行,满就必须换行了80
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y ++;
    }

    //滚动屏幕
    scroll();

    //移动硬件的输入光标
    move_cursor();
}

void console_write(char *cstr)
{
    while (*cstr)
    {
        console_putc_color(*cstr++, rc_black, rc_white);
    }
}

void console_write_color(char *cstr, real_color_t back, real_color_t fore)
{
    while (*cstr)
    {
        console_putc_color(*cstr++, back, fore);
    }
}
