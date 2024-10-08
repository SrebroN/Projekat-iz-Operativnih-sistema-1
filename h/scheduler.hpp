//
// Created by os on 8/7/24.
//

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "list.hpp"
class TCB;

class Scheduler{
private:
    static List<TCB> readyCoroutineQueue;

public:
    static TCB* get();

    static void put(TCB *ccb);
};

#endif //SCHEDULER_HPP
