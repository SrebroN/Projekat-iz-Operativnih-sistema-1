#ifndef SYSCALL_CPP_HPP
#define SYSCALL_CPP_HPP
#include "syscall_c.hpp"
#include "../h/tcb.hpp"

void* operator new (size_t n);
void operator delete (void* p);
void* operator new[](size_t n);
void operator delete[](void* p);

class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    static int sleep (time_t);
protected:
    Thread ();
    virtual void run () {}
private:
    thread_t myHandle;
    void (*body)(void*);
    void* arg;
    static void ThreadWrapper(void* thread);
};

class Semaphore {
    public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
    int timedWait (time_t);
    int tryWait();
    private:
    int init;
    sem_t myHandle;
};

class Console {
    public:
    static char getc ();
    static void putc (char);
};
#endif //SYSCALL_CPP_HPP
