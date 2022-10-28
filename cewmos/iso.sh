#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/cewmos.kernel isodir/boot/cewmos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "cewmos" {
	multiboot /boot/cewmos.kernel
}
EOF
grub-mkrescue -o cewmos.iso isodir
