#ifndef SEM_HPP
#define SEM_HPP
#include "list.hpp"
#include "tcb.hpp"
#define SEMDEAD -1
class Sem {
public:
    ~Sem(){}
    static int createSemaphore(sem_t* handle, unsigned value);
    int close();
    int wait();
    int signal();
    int trywait();
private:
    Sem(unsigned value=1):value(value),isOpen(true){  }
    int value;
    bool isOpen;
    List<TCB> blockedQueue;
};



#endif //SEM_HPP
