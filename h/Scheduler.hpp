//
// Created by os on 8/1/22.
//

#ifndef PROJECT_BASE_V1_1_SCHEDULER_HPP
#define PROJECT_BASE_V1_1_SCHEDULER_HPP

#include "../h/Queue.hpp"
class TCB;


class Scheduler {
    static Queue<TCB> *readyQueue;

    Scheduler() = default;

    ~Scheduler() {
        delete readyQueue;
    }


public:
    Scheduler(const Scheduler&) = delete;
    Scheduler(Scheduler&&) = delete;
    Scheduler operator=(const Scheduler&) = delete;
    Scheduler operator=(Scheduler&&) = delete;

    static Scheduler* getInstance() {
        static Scheduler* scheduler;
        static bool flag = false;
        if (!flag) {
            scheduler = new Scheduler();
            readyQueue = new Queue<TCB>;

            flag = true;
        }
        return scheduler;
    }

    static TCB* get();
    static void put(TCB* tcb);
    static bool empty();

    void* operator new(uint64 n) {
        uint64 sizeInBlocks = n / MEM_BLOCK_SIZE;
        if (sizeInBlocks * MEM_BLOCK_SIZE < n ) sizeInBlocks += 1;
        return MemoryAllocator::mem_alloc(sizeInBlocks);
    }

    void operator delete(void* p) {
        MemoryAllocator::mem_free(p);
    }

};


#endif //PROJECT_BASE_V1_1_SCHEDULER_HPP
