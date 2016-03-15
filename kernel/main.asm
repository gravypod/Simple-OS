[BITS 32]
MBALIGN     equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MBALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .text
	global _start
	_start:

		mov esp, 0x7BFF

		push ebx
		push eax

		extern kernel_main
		call kernel_main
		jmp $

	global hang
	hang:
		cli
		hlt
		jmp $


	global enable_interrupts
	enable_interrupts:
		sti
		ret
