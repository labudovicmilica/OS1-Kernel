//
// Created by os on 8/9/22.
//

#ifndef PROJECT_BASE_V1_1_SEM_HPP
#define PROJECT_BASE_V1_1_SEM_HPP

#include "../lib/hw.h"
#include "Queue.hpp"
class TCB;

class Sem{
public:
    Sem(uint64 init = 1) : val(init), interrupted(false) { blockedQueue = new Queue<TCB>();}
    int wait();
    int signal();

    int value() const;

    static uint64 open_sem(Sem** handle, uint64 init);
    uint64 close_sem();

    void* operator new(uint64 n);
    void* operator new[](uint64 n);
    void operator delete(void* p);
    void operator delete[](void* p);

protected:
    void block();
    void unblock();

private:
    int val;
    Queue<TCB> *blockedQueue;
    bool interrupted;
};


#endif //PROJECT_BASE_V1_1_SEM_HPP
