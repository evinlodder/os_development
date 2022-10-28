#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/meatos.kernel isodir/boot/meatos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "meatos" {
	multiboot /boot/meatos.kernel
}
EOF
grub-mkrescue -o meatos.iso isodir
