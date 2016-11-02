#编译所有文件

C_SOURCES=$(shell find . -name "*.c")

#$(patsubst <pattern>,<replacement>,<text>)
#名称:模式字符串替换函数--patsubst.
#功能:查找<text>中的单词(单词以"回车","空格","Tab","换行"分割)是否符合模式<pattern>
#	如果匹配则用<replacement>替换.(<pattern>中的'%'为通配符,表示任意长度的字符串,
#	而<replacement>中的'%'对应的是<pattern>中'%'对应的字符串.可以用'\'转义,
#	以'\%'表示通配所有字符串)
#返回:函数返回被替换过后的字符串
C_OBJECTS=$(patsubst %.c, %.o, $(C_SOURCES))

S_SOURCES=$(shell find . -name "*.s")

S_OBJECTS=$(patsubst %.s, %.o, $(S_SOURCES))

CC=gcc

LD=ld

AS=nasm

RM=rm

#gcc的nostdlib:不要链接标准库文件,主要是c语言运行库
#gcc的-fno-builtin:禁止gcc编译器内置函数.
#m32是产生32位的代码
#gcc -fno-stack-protector:禁用堆栈保护
#gcc -gstabs:以stabs格式声称调试信息,并且包含仅供gdb额外调试信息.
#gcc -ggdb:尽可能的生成gdb的可以使用的调试信息.
#gcc -I:用来制定的头文件目录
CC_FLAGS= -c -Wall -ggdb -I -nostdlib -fno-builtin -m32 -fno-stack-protector -gstabs+ \
		  -Iinclude

#-T:指定链接脚本文件
#-m elf_i386:生成i386平台下的elf格式的可执行文件
LD_FLAGS= -T scripts/kernel.lds -m elf_i386 -nostdlib

#-g:调试信息有效
#-F:用来为输出文件选择一个调试格式,本次是stabs格式
#-f:指定输出文件格式,缺省的情况下,输出格式总是bin,本次是elf
AS_FLAGS= -felf -g -F stabs

#makefile中的第一个目标会被作为其默认目标,由于依赖关系,有的命令会被决议的.
all : $(C_OBJECTS) $(S_OBJECTS) link update

.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(CC_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(AS) $(AS_FLAGS) $<

link:
	@echo 连接内核文件
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o kernel

.PHONY:clean
clean:
	$(RM) $(C_OBJECTS) $(S_OBJECTS) kernel kernel.iso disk.img

.PHONY:update
update:
	#创建一个格式为qcow大小为1G名为disk.img的镜像文件
	qemu-img create -f qcow disk.img 1G
	cp kernel isodir/boot
	#生成启动镜像
	grub2-mkrescue -o kernel.iso isodir
	#-m 128:为虚拟机分配128m内存
	#-hda disk.img:刚才创建的硬盘文件
	#-cdrom kernel.iso 为虚拟机的光驱中插入光盘 kernel.iso
	#-boot d:虚拟机光盘启动
	qemu -m 128 -hda disk.img -cdrom kernel.iso -boot d

.PHONY:disk
disk:
	qemu-img create -f qcow disk.img 1G

.PHONY:iso
iso:
	cp kernel isodir/boot/
	grub2-mkrescue -o kernel.iso isodir

.PHONY:runiso
runiso:
	qemu -m 128 -hda disk.img -cdrom kernel.iso -boot d

.PHONY:debug
debug:
	#gdb -x scripts/gdbinit &
	qemu -s -m 128 -hda disk.img -cdrom kernel.iso -boot d
	sleep 1
