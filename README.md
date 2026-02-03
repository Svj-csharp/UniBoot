# UniBoot
**Uni**versal **Boot**loader. A simple self-written 32-bit operation system. Included a minimalistic bootloader and a simple kernel written on .c;

# Why its created?
- Allow people to easily create their own operational systems for various purposes that do not require multitasking.
- For practice
- For lulz

# Structure of the project:
- src - main folder
- run.sh - linux script for compile and run OS in QEMU.
- src/boot.asm - bootloader
- src/linker.ld - linker
- src/kernel.c - kernel
- src/libs/screen/output.h - header to allow make output without any troubles
- src/libs/screen/input.h - header to allow make input to terminal without any troubles

# How to run?
- Download nasm, i686-efi-gcc cross-compiler, qemu.
- use:
```bash
git clone https://github.com/Svj-csharp/UniBoot && cd UniBoot
chmod +x run.sh
./run.sh
```
