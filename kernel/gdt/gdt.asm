
global gdt_flush
extern gp
gdt_flush:
	lgdt [gp] ; Put GTD into the gpointer within gdt.h
	mov ax, 0x10     ; Offset in GDT to our data
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:gdt_flush_ret
gdt_flush_ret:
	ret