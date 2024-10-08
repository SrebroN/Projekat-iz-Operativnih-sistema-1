#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/syscall_c.hpp"
#include "../test/printing.hpp"
extern void userMain();

void wrapperMain(void* ptr){
    userMain();
}

int main(){
    Riscv::w_stvec((uint64)&Riscv::supervisorTrap);
    MemoryAlloc::memory_init();
    TCB *threads[5];
    thread_create(&threads[0], nullptr, nullptr );
    TCB::running = threads[0];
    thread_create( &threads[1], &wrapperMain, nullptr );

    while( !threads[1]->isFinished() ) {
        thread_dispatch();
    }

    for(auto &thread :threads){
        delete thread;
    }
    printString("Finished\n");
    return 0;
}