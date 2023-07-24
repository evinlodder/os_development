#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/vinos.kernel isodir/boot/vinos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "vinos" {
	multiboot /boot/vinos.kernel
}
EOF
grub-mkrescue -o vinos.iso isodir
