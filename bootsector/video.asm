
; ________________________________________________________________________________
;| A0000-BFFFF  |  128Kb     | Video Ram | VGA Frame Buffer                       |
;|______________|____________|___________|________________________________________|


bios_print_char:
	mov ah, 0x0E
	int 0x10
	ret
	
print: ; Print a character to 0x0e
	pusha
	call bios_print_char
	popa
	ret

print_string:
	pusha
	.loop:
		mov al, [bx]    ; load what `bx` points to
		cmp al, 0x0
		je print_string.return
		push bx			; save bx
		call bios_print_char
		pop bx          ; restore bx
		inc bx
		jmp print_string.loop
	.return:
		popa
		ret

;init_display: ; Init display mode
;	mov ah, 0
;	mov al, 0x13
;	int 0x10
;	ret
;
;draw_pixel: ; Draw a pixel
;	
;	call store_16
;	pop ax ; Pop color
;	pop dx ; Pop y
;	pop cx ; Pop x
;
;    ;mov al,       ; white
;    mov ah, 0x0c     ; put pixel
;    int 0x10         ; draw pixel
;
;    call ret_16
;	ret
;

;draw_line:
;
;	call store_16
;
;	pop dx ; y2
;	pop cx ; x2
;	pop bx ; y1
;	pop ax ; x1
;
;	mov [0x900], ax
;	mov [0x900 + 16], bx
;	
;	sub dx, bx
;	sub cx, ax
;
;	fild dx
;	fild cx
;	
;	fdivp st0, st1
;
;	fstp [esp]
;
;	pop eax
;
;	fild dx
;	fild cx
;	
;	fdivp st1, st0
;
;	fstp [esp]
;
;	pop ebx
;
;	.line_loop:
;		mov ax, [0x900]
;		mov bx, [0x900 + 16]
;		
;		pusha
;
;		push ax
;		push bx
;		push 15
;		call draw_pixel
;		
;		popa
;
;
;		add ax, edx
;		add bx, ecx
;		
;		mov [0x900], ax 
;		mov [0x900 + 16], bx
;
;		cmp [0x900], cx
;		jne draw_line.line_loop
;		cmp [0x900 + 16], dx
;		jne draw_line.line_loop
;		
;		push ax
;		push bx
;		push 15
;		call draw_pixel
;
;	call ret_16
;	ret
;
;
;	
;	
;clear_display:
;	mov ax , 0A000h ; The offset to video memory
;	mov es , ax ; We load it to ES through AX, becouse immediate operation is not allowed on ES
;	mov ax , 0 ; 0 will put it in top left corner. To put it in top right corner load with 320, in the middle of the screen 32010.
;	mov di , ax ; load Destination Index register with ax value (the coords to put the pixel)
;	mov dl , 7 ; Grey color.
;	mov [es:di] , dl ; And we put the pixel
;	ret
