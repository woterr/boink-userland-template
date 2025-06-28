CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra -Ilibc/include
LDFLAGS = -T linker.ld -nostdlib

OBJS = src/main.o build/crt0.o
LIBC = libc/build/libc.a

DISKNAME = testdisk

elf: $(OBJS) $(LIBC)
	$(LD) $(LDFLAGS) -o build/program.elf $(OBJS) $(LIBC)

binary: elf
	i686-elf-objcopy -O binary build/program.elf build/program.bin

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/crt0.o: crt/crt0.s
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBC):
	make -C libc

clean:
	rm -rf build $(OBJS)
	make -C libc clean
	
disk: binary
	glfs-mkfs $(DISKNAME).glfs
	glfs-add $(DISKNAME).glfs build/program.bin program.bin
	glfs-ls $(DISKNAME).glfs

elfdisk: elf
	glfs-mkfs $(DISKNAME).glfs
	glfs-add $(DISKNAME).glfs build/program.elf program.elf
	glfs-ls $(DISKNAME).glfs