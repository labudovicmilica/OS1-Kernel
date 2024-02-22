//
// Created by os on 7/31/22.
//

#ifndef PROJECT_BASE_V1_1_TCB_HPP
#define PROJECT_BASE_V1_1_TCB_HPP


#include "../lib/hw.h"
#include "Scheduler.hpp"
#include "MemoryAllocator.hpp"

struct Periodic {
    TCB* tcb;
    time_t time_left;

    Periodic(TCB* tcb, time_t time) : tcb(tcb), time_left(time) {}

    void* operator new(uint64 n) {
        uint64 sizeInBlocks = n / MEM_BLOCK_SIZE;
        if (sizeInBlocks * MEM_BLOCK_SIZE < n ) sizeInBlocks += 1;
        return MemoryAllocator::mem_alloc(sizeInBlocks);
    }

    void operator delete(void* p) {
        MemoryAllocator::mem_free(p);
    }
};

class TCB{

public:
    ~TCB() {

        delete stack;
    }

    bool isFinished() const;
    void setFinished(bool finished);

    bool isBlocked() const;
    void setBlocked(bool blocked);

    uint64 getTimeSlice() const;

    using Body = void (*)(void*);

    static int create_thread(TCB** myHandle, TCB::Body body, void* arg, void* stack_space);
    static int create_thread_only(TCB** myHandle, TCB::Body body, void* arg, void* stack_space);
    int thread_exit();
    int start();
    static void yield();

    static TCB* running;

    TCB(const TCB&) = delete;
    TCB& operator=(const TCB&) = delete;
    static int sleep(time_t time);
    static Queue<Periodic> *sleepingQueue;
private:
    TCB(Body body, void* arg, void* stack_space) : body(body), arg(arg), stack((uint64*)stack_space),
                     context({(uint64) &threadWrapper, (uint64 )&stack[STACK_SIZE]}),
                     finished(false), blocked(false), idle(false), timeSlice(DEFAULT_TIME_SLICE) { }

    struct Context{
        uint64 ra;
        uint64 sp;
    };
    static bool madeSleep;
    static TCB* idleThread;
    Body body;
    void* arg;
    uint64* stack;
    Context context;
    bool finished;
    bool blocked;
    bool idle;


    uint64 timeSlice;
    static uint64 timeSliceCounter;

    friend class Riscv;

    static void contextSwitch(Context* oldContext, Context* runningContext);

    static void threadWrapper();

    static void dispatch();

    static uint64 constexpr STACK_SIZE = 8*DEFAULT_STACK_SIZE;

public:
    void* operator new(uint64 n) {
        uint64 sizeInBlocks = n / MEM_BLOCK_SIZE;
        if (sizeInBlocks * MEM_BLOCK_SIZE < n ) sizeInBlocks += 1;
        return MemoryAllocator::mem_alloc(sizeInBlocks);
    }

    void* operator new[](uint64 n) {
        uint64 sizeInBlocks = n / MEM_BLOCK_SIZE;
        if (sizeInBlocks * MEM_BLOCK_SIZE < n ) sizeInBlocks += 1;
        return MemoryAllocator::mem_alloc(sizeInBlocks);
    }

    void operator delete(void* p) {
        MemoryAllocator::mem_free(p);
    }

    void operator delete[](void* p) {
        MemoryAllocator::mem_free(p);
    }

};


#endif //PROJECT_BASE_V1_1_TCB_HPP
