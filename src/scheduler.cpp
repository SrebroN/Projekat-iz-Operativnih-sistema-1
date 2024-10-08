//
// Created by os on 8/7/24.
//
#include "../h/scheduler.hpp"

List<TCB>Scheduler::readyCoroutineQueue;

TCB *Scheduler::get(){
    return readyCoroutineQueue.removeFirst();
}

void Scheduler::put(TCB *ccb){
    readyCoroutineQueue.addLast(ccb);
}