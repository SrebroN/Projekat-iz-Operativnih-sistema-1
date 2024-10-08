.extern _ZN5Riscv20handleSupervisorTrapEmmmmm

.align 4
.global _ZN5Riscv14supervisorTrapEv
.type _ZN5Riscv14supervisorTrapEv, @function
_ZN5Riscv14supervisorTrapEv:
    #push all registers to stack
    addi sp, sp, -256
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,1,3,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)
    .endr

    call _ZN5Riscv20handleSupervisorTrapEmmmmm

 /*   csrr a1, scause
    addi a1, a1, -8
    beqz a1, syscall
    addi a1, a1, -1
    bnez a1, noSyscall

syscall:
    csrr a1,sscratch
    sd a1,8*10(sp)*/

noSyscall:
    #pop all registers from stack
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,1,3,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)
    .endr
    addi sp,sp, 256

    sret
