#! /bin/bash
qemu-system-i386 -no-kvm -D qemu.log -s -S -kernel kernel.bin &
gdb -x gdb.settings kernel.bin
kill $! > /dev/null