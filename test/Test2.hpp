//
// Created by os on 9/1/22.
//

#ifndef PROJECT_BASE_TEST2_HPP
#define PROJECT_BASE_TEST2_HPP

#endif //PROJECT_BASE_TEST2_HPP

#include "../h/syscall_c.hpp"
#include "printing.hpp"
#include "../h/syscall_cpp.hpp"

bool finishedA = false;
bool finishedB = false;
bool finishedC = false;

Semaphore* semaphore;

class WorkerA: public PeriodicThread {
public:
    WorkerA(): PeriodicThread(5) {}
protected:
    void periodicActivation() override {
        printString("Thread A \n");
    }
};

class WorkerB: public PeriodicThread {
public:
    WorkerB():PeriodicThread(5) {}

protected:
    void periodicActivation() override {
        printString("Thread B \n");
    }
};

class WorkerC: public PeriodicThread {
public:
    WorkerC():PeriodicThread(5) {}

protected:
    void periodicActivation() override {
        printString("Thread C \n");
    }
};


void test2() {
    PeriodicThread *threads[3];

    threads[0] = new WorkerA();
    printString("ThreadA created\n");

    threads[1] = new WorkerB();
    printString("ThreadB created\n");

    threads[2] = new WorkerC();
    printString("ThreadC created\n");

    semaphore = new Semaphore(1);

    for (int i = 0; i < 3; i++) {
        threads[i]->start();
    }
    Thread::dispatch();
    time_sleep(10);
    threads[1]->stopThread();
    finishedB = true;

    while (!(finishedA && finishedB && finishedC)) {
        Thread::dispatch();
        time_sleep(100);
        finishedA = true;
        finishedC = true;

    }


    for (auto thread: threads) { delete thread; }

}