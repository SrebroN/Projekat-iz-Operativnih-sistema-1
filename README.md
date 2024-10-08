# Projekat-iz-Operativnih-sistema-1
Multithreaded OS kernel for riscv

OS kernel written for RiscV architecture ran on qemu emulator. No external libraries are used, everything is written from scratch.
This project includes the following: memory managing, threads, semaphores, interrupt handling, synchronous context change, system and user mode.
Functionalities are implemented through:
- ABI(application binary interface) used for system calls called by software interrupts,
- C API(application programming interface), a wrapper for ABI which implements system calls as C functions,
- C++ OO API, an object oriented wrapper for functions from C API.
