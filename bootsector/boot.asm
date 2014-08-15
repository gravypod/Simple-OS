[BITS 16]
[ORG 0x7C00] ; Welcome everyone to 0x7c00.

call init_store_16
;call init_display

mov bx, STARTUP_MESSAGE
call print_string

;printing:
;
;call read_key
;
;mov al, [key]
;cmp al, 0x61
;jne printing
;
;call bios_print_char
;
;jmp printing

;mov bx, STARTUP_MESSAGE
;call print_string

call hault

STARTUP_MESSAGE:
	db "Loading OS" , 0
;CHARACTER_A:
;	db "a"


%include "utils.asm" ; Has convionience methods
%include "video.asm"
;%include "keyboard.asm"


;key db 0x00

times 510-($-$$) db 0 ; Writepad the bootsector
dw 0xaa55 ; Write our magic bytes