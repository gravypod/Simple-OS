#!/bin/bash
cd bootsector
./buildboot.sh
cd ../

qemu-system-x86_64 boot.bin

