#include "../h/syscall_cpp.hpp"
#include "../lib/hw.h"
#include "../lib/console.h"
#include"../h/memory.hpp"

void *operator new(size_t n){
   return mem_alloc(n);
}

void *operator new[](size_t n){
   return mem_alloc(n);
}

void operator delete(void*p){
    mem_free(p);
}

void operator delete[](void*p){
    mem_free(p);
}

Thread::Thread (void (*body)(void*), void* arg):myHandle(nullptr),body(body),arg(arg){}

Thread::~Thread (){
    thread_exit();
}

int Thread::start (){
    if(body==nullptr){
        thread_create(&myHandle,&Thread::ThreadWrapper,(void*)this);
    }else{
        thread_create(&myHandle,body,arg);
    }
    return 0;
}

void Thread::ThreadWrapper(void* thread){
    Thread* thr;
    thr=(Thread*)thread;
    thr->run();
}

void Thread::dispatch (){
    thread_dispatch();
}

int Thread::sleep (time_t){
    return 0;
}

Thread::Thread():myHandle(nullptr),body(nullptr),arg(nullptr){}

Semaphore::Semaphore (unsigned init):init(init){
    sem_open(&myHandle,init);
}

Semaphore::~Semaphore (){
}

int Semaphore::wait (){
    return sem_wait(myHandle);
}

int Semaphore::signal (){
    return sem_signal(myHandle);
}

int Semaphore::timedWait (time_t){
    return 0;
}

int Semaphore::tryWait(){
    return sem_trywait(myHandle);
}

char Console::getc(){
    return ::getc();
}

void Console::putc(char c){
    ::putc(c);
}