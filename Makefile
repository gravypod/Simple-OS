C_SOURCES = $(wildcard kernel/*.c)
HEADERS = $(wildcard kernel/*.h)
OBJ = ${C_SOURCES:.c=.o}
all: kernel.bin

run: all
	qemu-system-i386 -kernel kernel.bin


%.o : %.c ${HEADERS}
	gcc -m32 -std=c99 -ffreestanding -c $< -o $@

kernel_entry.o: kernel/kernel_entry.asm
	nasm kernel/kernel_entry.asm -f elf -o kernel_entry.o


kernel.bin : kernel_entry.o ${OBJ}
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat=elf32-i386

clean:
	rm -rf *.bin *.dis *.o
	rm -rf kernel/*.o