; Address allocations
; ________________________________________________________________________________
;| HEX Location |  Size      | Type      | Description                            |
;|______________|____________|___________|________________________________________|
;| 0-3FF        |  1Kb       | Ram       | Real Mode Interrupt Vector Table (IVT) |
;|______________|____________|___________|________________________________________|
;| 400-4FF      |  256 bytes | Ram       | BIOS Data Area (BDA)                   |
;|______________|____________|___________|________________________________________|
;| 500-9FBFF    |  630Kb     | Ram       | Free Memory                            |
;|______________|____________|___________|________________________________________|
;| 9FC00-9FFFF  |  1Kb       | Ram       | Extended BIOS Area (EBDA)              |
;|______________|____________|___________|________________________________________|
;| A0000-BFFFF  |  128Kb     | Video Ram | VGA Frame Buffer                       |
;|______________|____________|___________|________________________________________|
;| C0000-C7FFF  |  32Kb      | Rom       | Video Bios                             |
;|______________|____________|___________|________________________________________|
;| C8000-EFFFF  |  160kb     | Rom       | Misc.                                  |
;|______________|____________|___________|________________________________________|
;| F0000-FFFFF  |  64Kb      | Rom       | BIOS                                   |
;|______________|____________|___________|________________________________________|

init_store_16:
	mov bx, [0x500 + 16]
	mov [0x500], bx
	ret

; 0x500 is pointer to last stored 16 bit value
store_16:

	pop ax ; Store ret address for store_16
	pop cx ; 16 bit value to store

	push ax

	mov bx, [0x500] ; Where can our next value go?
	mov [bx], cx
	add bx, 16
	mov [0x500], bx

	ret 

ret_16: ; Fetch stored value and place on stack
	
	pop ax ; Return address for ret_16
	
	mov bx, [0x500]
	sub bx, 16
	mov cx, [bx]
	
	mov [0x500], bx

	push cx ; Put our initial register back onto the stack
	push ax ; push return address onto the stack
	ret

hault: ; Hault the CPU forever
	cli
	hlt
	ret
