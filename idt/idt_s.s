; 定义两个构造中断处理函数的宏有的中断有错误代码,有的没有()

; 用于没有错误代码的中断
%macro ISR_NOERRCODE 1
[GLOBAl isr%1]
isr%1:
        cli             ; 首先关闭中断
        push 0          ; push 无效的中断错误代码
        push %1         ; push 中断号
        jmp isr_common_stub
%endmacro

; 用于有错误代码的中断
%marco ISR_ERRCODE 1
[GLOBAL isr%1]
isr%1:
        cli             ; 关闭中断
        push %1         ; push 中断号
        jmp isr_common_stub'
%endmacro

; 定义中断处理函数
ISR_NOERRCODE 0		; 0 #DE 除 0 异常
ISR_NOERRCODE 1         ; 1 #DB 异常调试
ISR_NOERRCODE 2         ; 2 NMI
ISR_NOERRCODE 3         ; 3 BP 断点异常
ISR_NOERRCODE 4         ; 4 #OF 溢出
ISR_NOERRCODE 5         ; 5 #BR 对数组的引用超出边界
ISR_NOERRCODE 6         ; 6 #UD 无效或未定义的操作码
ISR_NOERRCODE 7         ; 7 #NM 设备不可用无数学协处理器
ISR_ERRCODE   8         ; 8 #DF 双重故障有错误代码
ISR_NOERRCODE 9         ; 9 协处理器跨段操作
ISR_ERRCODE   10        ; 10 #TS 无效TSS有错误代码
ISR_ERRCODE   11        ; 11 #NP 段不存在有错误代码
ISR_ERRCODE   12        ; 12 #ss 栈错误有错误代码
ISR_ERRCODE   13        ; 13 #GP 常规有保护代码
ISR_ERRCODE   14        ; 14 #PF 页故障有错误代码
ISR_NOERRCODE 15        ; 15 CPU保留
ISR_NOERRCODE 16        ; 16 #MF 浮点处理单元错误
ISR_ERRCODE   17        ; 17 #AC 对齐检查
ISR_NOERRCODE 18        ; 18 #MC 机器检查
ISR_NOERRCODE 19        ; 19 #XM SIMD单指令多数据 浮点异常


; 20 ~ 31 Intel 保留
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

; 255 用户自定义
ISR_NOERRCODE 255
