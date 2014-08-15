read_key:
	mov ah, 0x01
	int 0x21
	mov [key], al
	ret