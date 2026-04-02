set -e

qemu-system-i386 -cdrom myos.iso -d int,cpu_reset -no-shutdown -no-reboot -D log.txt | head -50
