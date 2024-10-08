#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/scheduler.hpp"
#include "../test/printing.hpp"

TCB *TCB::running=nullptr;

int TCB::createThread(thread_t*handle,Body body, void *arg, char* stack) {
    *handle = new TCB(body,arg,stack);
    return 0;
}

void TCB::exit() {
    running->setFinished(true);
    dispatch();
}

void TCB::popSppSpie(){
    Riscv::mc_sstatus(Riscv::SSTATUS_SPP);
    __asm__ volatile ("csrw sepc,ra");
    __asm__ volatile ("sret");
}


void TCB::dispatch() {
    TCB *old=running;
    if(!old->isFinished() && !old->isBlocked()) { Scheduler::put(old);}
    running=Scheduler::get();
    if(running!=old) {
        TCB::contextSwitch(&old->context,&running->context);
    }
}

void TCB::threadWrapper() {
    popSppSpie();
    running->body(running->arg);
    thread_exit();
}