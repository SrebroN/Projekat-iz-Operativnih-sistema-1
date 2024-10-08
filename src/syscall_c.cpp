#include "../h/syscall_c.hpp"
#include "../h/memory.hpp"
#include "../h/riscv.hpp"


uint64 syscall(uint64 code,uint64 arg0,uint64 arg1,uint64 arg2,uint64 arg3){
	uint64 ret;
	asm volatile("mv a0, %0" ::"r"(code));
	asm volatile("mv a1, %0" ::"r"(arg0));
    asm volatile("mv a2, %0" ::"r"(arg1));
    asm volatile("mv a3, %0" ::"r"(arg2));
	asm volatile("mv a4, %0" ::"r"(arg3));
    asm volatile("ecall");
    asm volatile("mv %0,a0":"=r"(ret));
	return ret;
}

void*mem_alloc(size_t size){
    size+=sizeof(MemoryHeader);
    size_t sizeInBlocks=size/MEM_BLOCK_SIZE+(size%MEM_BLOCK_SIZE==0?0:1);
	return (void*)syscall(MEM_ALLOC,(uint64)sizeInBlocks,0,0,0);
}

int mem_free(void* pointer){
	return (int)syscall(MEM_FREE,(uint64)pointer,0,0,0);
}

int thread_create(thread_t* handle, void(*start_routine)(void *), void *arg) {
    void *stack_space=(start_routine!=nullptr?(void*)new char[DEFAULT_STACK_SIZE]:nullptr);
	return (int)syscall(THREAD_CREATE,(uint64)handle,(uint64)start_routine,(uint64)arg,(uint64)stack_space);
}

int thread_exit(){
	return (int)syscall(THREAD_EXIT,0,0,0,0);
}

void thread_dispatch(){
	return (void)syscall(THREAD_DISPATCH,0,0,0,0);
}

int sem_open(sem_t*handle,unsigned init){
    return (int)syscall(SEM_OPEN,(uint64)handle,(uint64)init,0,0);
}

int sem_close(sem_t handle){
    return (int)syscall(SEM_CLOSE,(uint64)handle,0,0,0);
}

int sem_wait(sem_t id){
    return (int)syscall(SEM_WAIT,(uint64)id,0,0,0);
}

int sem_signal(sem_t id){
    return (int)syscall(SEM_SIGNAL,(uint64)id,0,0,0);
}

int sem_trywait(sem_t id){
    return (int)syscall(SEM_TRYWAIT,(uint64)id,0,0,0);
}

char getc(){
	return (char)syscall(GETC,0,0,0,0);
}

void putc(char c){
	return (void)syscall(PUTC,(uint64)c,0,0,0);
}

