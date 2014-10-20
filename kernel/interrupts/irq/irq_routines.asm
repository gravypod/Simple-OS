section .text
	extern irq_handler
	global irq_0
	global irq_1
	global irq_2
	global irq_3
	global irq_4
	global irq_5
	global irq_6
	global irq_7
	global irq_8
	global irq_9
	global irq_10
	global irq_11
	global irq_12
	global irq_13
	global irq_14
	global irq_15
	
	irq_0:
		cli
		push byte 0
		push byte 32
		jmp irq_default
	irq_1:
		cli
		push byte 0
		push byte 33
		jmp irq_default
	irq_2:
		cli
		push byte 0
		push byte 34
		jmp irq_default
	irq_3:
		cli
		push byte 0
		push byte 35
		jmp irq_default
	irq_4:
		cli
		push byte 0
		push byte 36
		jmp irq_default
	irq_5:
		cli
		push byte 0
		push byte 37
		jmp irq_default
	irq_6:
		cli
		push byte 0
		push byte 38
		jmp irq_default
	irq_7:
		cli
		push byte 0
		push byte 39
		jmp irq_default
	irq_8:
		cli
		push byte 0
		push byte 40
		jmp irq_default
	irq_9:
		cli
		push byte 0
		push byte 41
		jmp irq_default
	irq_10:
		cli
		push byte 0
		push byte 42
		jmp irq_default
	irq_11:
		cli
		push byte 0
		push byte 43
		jmp irq_default
	irq_12:
		cli
		push byte 0
		push byte 44
		jmp irq_default
	irq_13:
		cli
		push byte 0
		push byte 45
		jmp irq_default
	irq_14:
		cli
		push byte 0
		push byte 46
		jmp irq_default
	irq_15:
		cli
		push byte 0
		push byte 47
		jmp irq_default
	irq_default:
		pusha
		push ds
		push es
		push fs
		push gs
		mov ax, 0x10 ; Kernel segment
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov eax, esp
		push eax
		mov eax, irq_handler
		call eax
		pop eax
		pop gs
		pop fs
		pop es
		pop ds
		popa
		add esp, 8
		iret