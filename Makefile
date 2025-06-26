CC = i686-elf-gcc
LD = i686-elf-ld
AR = i686-elf-ar
CFLAGS = -ffreestanding -O2 -Wall -Wextra -Ilibc/include
LDFLAGS = -T linker.ld -nostdlib

OBJS = src/main.o libc/src/syscall.o libc/src/stdio.o libc/src/stdlib.o

binary: $(OBJS)
	$(LD) $(LDFLAGS) -o build/program.elf $(OBJS)
	i686-elf-objcopy -O binary build/program.elf build/program.bin

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

libc/src/%.o: libc/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.bin build/*.elf $(OBJS)