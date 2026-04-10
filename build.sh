set -ex

nasm -f elf32 boot.s -o boot.o
nasm -f elf32 macros.s -o macros.o

~/opt/cross/bin/i686-elf-gcc -g -c pic.c -o pic.o -std=gnu99 -ffreestanding -Wall -Wextra
~/opt/cross/bin/i686-elf-gcc -g -c ssfn.c -o ssfn.o -std=gnu99 -ffreestanding -Wall -Wextra
~/opt/cross/bin/i686-elf-gcc -g -c excepthandler.c -o excepthandler.o -std=gnu99 -ffreestanding -Wall -Wextra
~/opt/cross/bin/i686-elf-gcc -g -c gdt.c -o gdt.o -std=gnu99 -ffreestanding -fno-omit-frame-pointer -Wall -Wextra
~/opt/cross/bin/i686-elf-gcc -g -c -O0 kernel.c -o kernel.o -std=gnu99 -ffreestanding -fno-omit-frame-pointer -Wall -Wextra
~/opt/cross/bin/i686-elf-gcc -g -T linker.ld -o myos -ffreestanding -fno-omit-frame-pointer -nostdlib boot.o kernel.o gdt.o inlineas.o pic.o excepthandler.o macros.o ssfn.o u_vga16.o -lgcc

rm -rf isodir
mkdir -p isodir/boot/grub
cp myos isodir/boot/myos
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir
