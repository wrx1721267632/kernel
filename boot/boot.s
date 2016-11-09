;内核开始

;可查看multiboot规范

;Multiboot 魔数,由规范决定
MBOOT_HEADER_MAGIC equ 0x1BADB002

;0号位表示将所有的引导块按页(4K)边界对齐
MBOOT_PAGE_ALIGN   equ 1 << 0

;1号位表示boot_device域有效,并指出引导程序从那个BIOS磁盘设备载入OS映像.
MBOOT_HEADER_INFO  equ 1 << 1

;定义我们使用的标记
MBOOT_HEADER_FLAGS equ (MBOOT_PAGE_ALIGN | MBOOT_HEADER_INFO)

;域check是一个32位无符号值,当与其他的magic域(也就是magic和flags)相加时,
;结果之和为32位的无符号值0(即magic+flags+checksun = 0)
MBOOT_CHECKSUM     equ -(MBOOT_HEADER_MAGIC+MBOOT_HEADER_FLAGS)

;multboot头的magic域所必需的
;   0   u32 magic必须
;   4   u32 flags必须
;   8   u32 checksum必须
;

[BITS 32]

section .init.text

;在代码段起始位设置符合Multiboot规范的标记

dd MBOOT_HEADER_MAGIC   ;GRUB通过这个魔数判断该映像是否支持
dd MBOOT_HEADER_FLAGS   ;GRUB的一些加载时选项,其详细注释在定义处
dd MBOOT_CHECKSUM   ;检测数值,其含义在定义处

[GLOBAL start]          ;向外部声明内核代码入口,此处提供该声明给链接器
[GLOBAL mboot_ptr_tmp]  ;向外部声明struct multiboot *变量
[EXTERN kern_entry]     ;声明内核c代码入口地址

start:
        cli                     ;此时还没有设置好保护模式的中断处理
                                ;所以必须关中断
        mov [glb_mboot_ptr]     ;将 ebx 中存储的指针存入 glb_mboot_ptr 变量
        mov esp, STACK_TOP      ;设置内核栈地址, 按照 multiboot 规范
        and esp, 0FFFFFFF0H     ;栈地址按照 16 字节对齐
        mov ebp, 0              ;帧指针修改为 0
        call kern_entry         ;调用内核入口函数


section .init.data          ;开启分页前临时的数据段
stack:  times 1024 db 0     ;这里作为临时内核栈
STACK_TOP equ $-stack-1     ;内核栈顶, $ 符指代是当前地址

glb_mboot_ptr:  dd 0        ; 全局 multiboot 结构体指针

;[BITS 32]           ;所有代码以32位的方式编译
;;section .text       ;代码段开始
;
;;在代码段起始位设置符合Multiboot规范的标记
;
;dd MBOOT_HEADER_MAGIC   ;GRUB通过这个魔数判断该映像是否支持
;dd MBOOT_HEADER_FLAGS   ;GRUB的一些加载时选项,其详细注释在定义处
;dd MBOOT_CHECKSUM   ;检测数值,其含义在定义处
;
;[GLOBAL start]          ;向外部声明内核代码入口,此处提供该声明给链接器
;[GLOBAL glb_mboot_ptr]  ;向外部声明struct multiboot *变量
;[EXTERN kern_entry]     ;声明内核c代码入口地址
;
;start:
;    cli                         ;此时还没有设置好中断处理,要关闭中断
;
;    mov esp, STACK_TOP          ;设置内核栈地址
;    mov ebp, 0                  ;将栈帧指针设置为0
;    and esp, 0FFFFFFF0H         ;栈地址按照字节对齐
;    mov [glb_mboot_ptr],ebx     ;将ebx中存储的指针存入全局变量
;    call kern_entry             ;调用内核初始函数
;
;stop:
;    hlt                         ;停机
;    jmp stop                    ;到这里结束
;
;section .bss                    ;未初始化的数据段
;stack:
;    resb 32768                  ;这里作为内核栈
;glb_mboot_ptr:                  ;全局的multiboot结构指针
;    resb 4
;STACK_TOP equ $-stack-1         ;内核栈顶,$表示当前地址

