//
// Created by os on 9/1/22.
//

#ifndef PROJECT_BASE_TEST1_HPP
#define PROJECT_BASE_TEST1_HPP

#endif //PROJECT_BASE_TEST1_HPP

#include "../h/syscall_c.hpp"

#include "printing.hpp"
#include "../h/syscall_cpp.hpp"


bool finishedA = false;
bool finishedB = false;
bool finishedC = false;

Semaphore* semaphore;

class WorkerA: public Thread {
    void workerBodyA(void* arg);
public:
    WorkerA():Thread() {}

    void run() override {
        workerBodyA(nullptr);
    }
};

class WorkerB: public Thread {
    void workerBodyB(void* arg);
public:
    WorkerB():Thread() {}

    void run() override {
        workerBodyB(nullptr);
    }
};

class WorkerC: public Thread {
    void workerBodyC(void* arg);
public:
    WorkerC():Thread() {}

    void run() override {
        workerBodyC(nullptr);
    }
};

void WorkerA::workerBodyA(void* arg) {
    for (uint64 i = 0; i < 10; i++) {
        semaphore->wait();
        printString("Thread A: id = ");
        int id = Thread::getThreadId();
        printInt(id);
        printString("\n");
        semaphore->signal();
        time_sleep(5);
    }
    printString("A finished!\n");
    finishedA = true;
}

void WorkerB::workerBodyB(void* arg) {
    for (uint64 i = 0; i < 10; i++) {
        semaphore->wait();
        printString("Thread B: id = ");
        int id = Thread::getThreadId();
        printInt(id);
        printString("\n");
        semaphore->signal();
        time_sleep(5);
    }
    printString("B finished!\n");
    finishedB = true;
}

void WorkerC::workerBodyC(void* arg) {
    for (uint64 i = 0; i < 10; i++) {
        semaphore->wait();
        printString("Thread C: id = ");
        int id = Thread::getThreadId();
        printInt(id);
        printString("\n");
        semaphore->signal();
        time_sleep(5);
    }
    printString("C finished!\n");
    finishedC = true;
}

void test1() {
    Thread* threads[3];

    threads[0] = new WorkerA();
    printString("ThreadA created\n");

    threads[1] = new WorkerB();
    printString("ThreadB created\n");

    threads[2] = new WorkerC();
    printString("ThreadC created\n");

    semaphore = new Semaphore(1);

    for(int i=0; i<3; i++) {
        threads[i]->start();
    }

    while (!(finishedA && finishedB && finishedC)) {
        Thread::dispatch();
    }

    for (auto thread: threads) { delete thread; }
}