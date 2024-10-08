#ifndef SYSCALL_C_HPP
#define SYSCALL_C_HPP

#include "../h/tcb.hpp"
#define MEM_ALLOC 0x01
#define MEM_FREE 0x02
#define THREAD_CREATE 0x11
#define THREAD_EXIT 0x12
#define THREAD_DISPATCH 0x13
#define SEM_OPEN 0x21
#define SEM_CLOSE 0x22
#define SEM_WAIT 0x23
#define SEM_SIGNAL 0x24
#define SEM_TRYWAIT 0x26
#define GETC 0x41
#define PUTC 0x42
class TCB;
typedef TCB* thread_t;
const int EOF=-1;
class Sem;
typedef Sem* sem_t;

void*mem_alloc(size_t size);
int mem_free(void*);
int thread_create (thread_t* handle, void(*start_routine)(void*), void*arg);
int thread_exit();
void thread_dispatch();
int sem_open(sem_t*handle,unsigned init);
int sem_close(sem_t handle);
int sem_wait(sem_t id);
int sem_signal(sem_t id);
int sem_trywait(sem_t id);
char getc();
void putc(char);

#endif //SYSCALL_C_HPP
