section .text
	update_cr0:
		push ebp
		mov ebp, esp ; Setup stack

		mov eax, [ebp + 8] ; Grab first address 