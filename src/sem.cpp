#include "../h/sem.hpp"

int Sem::createSemaphore(sem_t* handle, unsigned value){
    *handle=new Sem(value);
    if(handle==nullptr)return -1;
    return 0;
}
int Sem::close(){
    if(isOpen==false)return SEMDEAD;
    isOpen=false;
    for(TCB*tmp=blockedQueue.removeFirst();tmp;tmp=blockedQueue.removeFirst()){
        tmp->setBlocked(false);
    }
    return 0;
}
int Sem::wait(){
    if(isOpen==false)return SEMDEAD;
    if(--value<0){
        TCB::running->setBlocked(true);
        blockedQueue.addLast(TCB::running);
        TCB::dispatch();
        if(isOpen==false)return SEMDEAD;
    }
    return 0;
}
int Sem::signal(){
    if(isOpen==false)return SEMDEAD;
    if(++value<=0){
        TCB* tmp=blockedQueue.removeFirst();
        tmp->setBlocked(false);
        Scheduler::put(tmp);
    }
    return 0;
}
int Sem::trywait(){
    if(isOpen==false)return SEMDEAD;
    if(value==1 || value==0){
        value=0;
        return 0;
    }
    --value;
    return 1;
}