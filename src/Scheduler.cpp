//
// Created by os on 8/1/22.
//
#include "../test/printing.hpp"
#include "../h/Scheduler.hpp"

Queue<TCB> *Scheduler::readyQueue;

TCB *Scheduler::get() {
    getInstance();
    return readyQueue->remove();
}

void Scheduler::put(TCB *tcb) {
    getInstance();
    readyQueue->add(tcb);
    //printString("sch->put\n");
}

bool Scheduler::empty() {
    getInstance();
    if (readyQueue->peek() == nullptr) return true;
    else return false;
}

