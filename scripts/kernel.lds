ENTRY(start)    /*ENTRY(symbol),指定symbol就是链接器指定的内核的入口*/

SECTIONS {
            /* "."表示当前的虚拟地址,赋值语句的意思是将当前虚拟地址设置成0x100000
            *为什么是0x100000,grub从elf内核文件中读取物理地址(加载地址LMA),这个值
            *必须大于或等于1M,并且小于真实的物理地址RAM的大小.这是grub的限制,并不是
            *多启动机制的限制
            *0x100000 = 1M
            */
        . = 0x100000;
        PROVIDE( kern_start = .);
        .text :
        {
            *(.text)
            /* 段设置为4KB对齐*/
            . = ALIGN(4096);
        }

        .data :
        {
            *(.data)
            *(.rodata)
            . = ALIGN(4096);
        }

        .bss :
        {
            *(.bss)
            . = ALIGN(4096);
        }

        .stab :
        {
            *(.stab)
            . = ALIGN(4096);
        }

        .stabstr :
        {
            *(.stabstr)
            . = ALIGN(4096);
        }
        PROVIDE( kern_end = .);
}
