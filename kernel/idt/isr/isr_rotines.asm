
section .text
	extern isr_handler ; Name of the default ISR handler
	global isr_0       ; Divide by zero exception 
	global isr_1       ; Debug Exception 
	global isr_2       ; Non Maskable Interrupt Exception
	global isr_3       ; Breakpoint Exception
	global isr_4       ; Into Detected Overflow Exception
	global isr_5       ; Out of Bounds Exception
	global isr_6       ; Invalid Opcode Exception
	global isr_7       ; No Coprocessor Exception
	global isr_8       ; Double Fault Exception
	global isr_9       ; Coprocessor Segment Overrun Exception
	global isr_10      ; Bad TSS Exception
	global isr_11      ; Segment Not Present Exception
	global isr_12      ; Stack Fault Exception
	global isr_13      ; General Protection Fault Exception
	global isr_14      ; Page Fault Exception
	global isr_15      ; Unknown Interrupt Exception
	global isr_16      ; Coprocessor Fault Exception
	global isr_17      ; Alignment Check Exception (486+)
	global isr_18      ; Machine Check Exception (Pentium/586+)
	global isr_19      ; Reserved Exceptions (Unused?)
	global isr_20      ; Reserved Exceptions (Unused?)
	global isr_21      ; Reserved Exceptions (Unused?)
	global isr_22      ; Reserved Exceptions (Unused?)
	global isr_23      ; Reserved Exceptions (Unused?)
	global isr_24      ; Reserved Exceptions (Unused?)
	global isr_25      ; Reserved Exceptions (Unused?)
	global isr_26      ; Reserved Exceptions (Unused?)
	global isr_27      ; Reserved Exceptions (Unused?)
	global isr_28      ; Reserved Exceptions (Unused?)
	global isr_29      ; Reserved Exceptions (Unused?)
	global isr_30      ; Reserved Exceptions (Unused?)
	global isr_31      ; Reserved Exceptions (Unused?)
	
	isr_0:
		cli
		push byte 0
		push byte 0
		jmp isr_default
	isr_1:
		cli
		push byte 0
		push byte 1
		jmp isr_default
	isr_2:
		cli
		push byte 0
		push byte 2
		jmp isr_default
	isr_3:
		cli
		push byte 0
		push byte 3
		jmp isr_default
	isr_4:
		cli
		push byte 0
		push byte 4
		jmp isr_default
	isr_5:
		cli
		push byte 0
		push byte 5
		jmp isr_default
	isr_6:
		cli
		push byte 0
		push byte 6
		jmp isr_default
	isr_7:
		cli
		push byte 0
		push byte 7
		jmp isr_default
	isr_8:
		cli
		push byte 8 ; Push byte 0 is not needed
					; Already exists on the stack
		jmp isr_default
	isr_9:
		cli
		push byte 0
		push byte 9
		jmp isr_default
	isr_10:
		cli
		push byte 0
		push byte 10
		jmp isr_default
	isr_11:
		cli
		push byte 0
		push byte 11
		jmp isr_default
	isr_12:
		cli
		push byte 0
		push byte 12
		jmp isr_default
	isr_13:
		cli
		push byte 0
		push byte 13
		jmp isr_default
	isr_14:
		cli
		push byte 0
		push byte 14
		jmp isr_default
	isr_15:
		cli
		push byte 0
		push byte 15
		jmp isr_default
	isr_16:
		cli
		push byte 0
		push byte 16
		jmp isr_default
	isr_17:
		cli
		push byte 0
		push byte 17
		jmp isr_default
	isr_18:
		cli
		push byte 0
		push byte 18
		jmp isr_default
	isr_19:
		cli
		push byte 0
		push byte 19
		jmp isr_default
	isr_20:
		cli
		push byte 0
		push byte 20
		jmp isr_default
	isr_21:
		cli
		push byte 0
		push byte 21
		jmp isr_default
	isr_22:
		cli
		push byte 0
		push byte 22
		jmp isr_default
	isr_23:
		cli
		push byte 0
		push byte 23
		jmp isr_default
	isr_24:
		cli
		push byte 0
		push byte 24
		jmp isr_default
	isr_25:
		cli
		push byte 0
		push byte 25
		jmp isr_default
	isr_26:
		cli
		push byte 0
		push byte 26
		jmp isr_default
	isr_27:
		cli
		push byte 0
		push byte 27
		jmp isr_default
	isr_28:
		cli
		push byte 0
		push byte 28
		jmp isr_default
	isr_29:
		cli
		push byte 0
		push byte 29
		jmp isr_default
	isr_30:
		cli
		push byte 0
		push byte 30
		jmp isr_default
	isr_31:
		cli
		push byte 0
		push byte 31
		jmp isr_default
	
	
	
	
	; Save registers and sets up kernel mode
	; Call isr_handler
	; Restores stack frame
	isr_default:
		pusha ; Save all of our registers
		push ds
		push es
		push fs
		push gs
		mov ax, 0x10 ; Load the kernel GDT segmant
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov eax, esp ; Creat stack
		push eax
		mov eax, isr_handler
		call eax ; Cll the handler
		pop eax
		pop gs
		pop fs
		pop es
		pop ds
		popa
		add esp, 8
		iret