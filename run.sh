#!/bin/bash


SRC_DIR="src"
LIB_SCREEN_DIR="libs/screen"
BUILD_DIR="build"


mkdir -p $BUILD_DIR

echo "Сборка"


echo "1. Компиляция boot.asm..."
nasm -f elf32 $SRC_DIR/boot.asm -o $BUILD_DIR/boot.o

echo "2. Компиляция output.c..."
gcc -m32 -c $SRC_DIR/libs/screen/output.c -o $BUILD_DIR/output.o \
    -ffreestanding -nostdlib -fno-stack-protector -I$SRC_DIR

echo "3. Компиляция input.c..."
gcc -m32 -c $SRC_DIR/libs/screen/input.c -o $BUILD_DIR/input.o \
    -ffreestanding -nostdlib -fno-stack-protector -I$SRC_DIR

echo "4. Компиляция kernel.c..."
gcc -m32 -c $SRC_DIR/kernel.c -o $BUILD_DIR/kernel.o \
    -ffreestanding -nostdlib -fno-stack-protector -I$SRC_DIR


echo "5. Линковка..."
ld -m elf_i386 -Ttext 0x1000 \
    $BUILD_DIR/boot.o \
    $BUILD_DIR/kernel.o \
    $BUILD_DIR/output.o \
    $BUILD_DIR/input.o \
    -o $BUILD_DIR/kernel.bin


qemu-system-i386 -kernel $BUILD_DIR/kernel.bin