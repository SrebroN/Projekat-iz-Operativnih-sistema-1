#ifndef TCB_HPP
#define TCB_HPP

#include "scheduler.hpp"
#include "../lib/hw.h"
#include "../h/memory.hpp"
#include "../h/syscall_c.hpp"

typedef TCB* thread_t;
class TCB{
public:
    static void dispatch();
    static void exit();
    ~TCB() {
        MemoryAlloc::mem_free(stack);
    }
    bool isFinished()const{
        return finished;
    }
    bool isBlocked()const {
        return blocked;
    }
    void setFinished(bool finished){
        this->finished=finished;
    }
    void setBlocked(bool blocked) {
        this->blocked=blocked;
    }
    using Body=void(*)(void*);


    static int createThread(thread_t*handle,Body body, void *arg, char* stack);


    static TCB *running;

private:


    TCB(Body body,void*arg,char* stack):
             body(body),arg(arg),
             stack(body!=nullptr?new char[DEFAULT_STACK_SIZE]:nullptr),
             context({(uint64)&threadWrapper,stack!=nullptr?(uint64)(&stack[STACK_SIZE]):0}),
             finished(false),
             blocked(false){
        if(body!=nullptr) {
            Scheduler::put(this);
        }
    }
    struct Context{
        uint64 ra;
        uint64 sp;
    };

    Body body;
    void *arg;
    char* stack;
    Context context;
    bool finished;
    bool blocked;
    friend class Riscv;
    friend class Thread;
    static void threadWrapper();

    static void contextSwitch(Context *oldContext,Context *runningContext);
    static void popSppSpie();
    
    static uint64 constexpr STACK_SIZE=DEFAULT_STACK_SIZE;
    static uint64 constexpr TIME_SLICE=DEFAULT_TIME_SLICE;
};


#endif //TCB_HPP
