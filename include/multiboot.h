/*************************************************************************
	> File Name: include/multiboot.h
	> Author:
	> Mail:
	> Created Time: 2016年10月30日 星期日 16时36分45秒
 ************************************************************************/

#ifndef _INCLUDE_MULTIBOOT_H
#define _INCLUDE_MULTIBOOT_H

#include"types.h"

typedef
struct multiboot_t{
    uint32_t flags;                 //multiboot的版本信息
    /*
     * 从BIOS获知的可用内存
     * mem_lower 和 mem_upper分别指出了低端和高端内存的大小,单位是 K
     * 低端内存的首地址是 0, 高端内存的首地址是 1M
     * 低端内存的最大可能值是640K
     * 高端内存的最大可能值是最大值减去 1M.但并不保证是这个值.
     */
    uint32_t mem_lower;
    uint32_t mem_upper;

    uint32_t boot_device;           //指出引导程序从那个磁盘设备载入的映像BIOS
    uint32_t cmdline;               //内核命令行
    uint32_t mods_count;            //boot 模块列表
    uint32_t mods_addr;

    /*
     * ELF 格式内核映像的section 头表.包括每项的大小,共有几项以及作为名字索引的字符串
     */
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;

    /*
     * 以下两项指出保存由BIOS提供的内存分布的缓冲区的地址和长度
     * mmap_addr 是缓冲区地址,mmap_length 是缓冲区的总大小
     * 缓冲区由一个或多个下面的 mmap_entry_t 组成
     */
    uint32_t mmap_length;
    uint32_t mmap_addr;

    uint32_t drives_addr;           //指出第一个驱动器结构的物理地址
    uint32_t drives_length;         //指出第一个驱动器结构的大小
    uint32_t config_table;          //ROM配置表
    uint32_t boot_loader_name;      //boot loader 的名字
    uint32_t apm_table;             //APM表
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;



/*
 * size 是相关结构的大小,单位是字节,他可能大于最小值 20
 * base_addr_low 是启动地址的低位, base_addr_high 是高32位,  启动地址共64位
 * length_low 是内存区域大小的低位, length_high 是内存区域大小的高 32 位, 共64位
 * type 是相应地址区间的类型, 1 代表可用,所有其他的值代表保留区域 RAM
 */
typedef
struct mmap_entry_t {
    uint32_t size;              //size 是不含自身变量的大小
    uint32_t base_addr_low;
    uint32_t base_addr_high;
    uint32_t length_low;
    uint32_t length_high;
    uint32_t type;
} __attribute__((packed)) mmap_entry_t;

/* 声明全局变量的 multiboot* 指针 */
extern multiboot_t *glb_mboot_ptr;

#endif
