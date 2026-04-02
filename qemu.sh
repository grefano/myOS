set -e

qemu-system-i386 -cdrom myos.iso -d int 2>&1 | head -50
