set -e

qemu-system-i386 -cdrom myos.iso -s -S -d int,cpu_reset -no-shutdown -no-reboot -D log.txt &
sleep 2
gdb isodir/boot/myos -x debug.gdb
