//
// Created by os on 7/25/22.
//

#include "../lib/console.h"
#include "../h/syscall_c.hpp"
#include "../test/printing.hpp"
#include "../h/Riscv.hpp"
#include "../h/TCB.hpp"
void userMain();

bool userFinished = false;


void wrapperMain(void* arg){
    userMain();
    userFinished = true;
}

void main() {

    Riscv::w_stvec((uint64) Riscv::supervisorTrap);


    void* stack = MemoryAllocator::mem_alloc(8*DEFAULT_STACK_SIZE/64);
    void* stack0 = MemoryAllocator::mem_alloc(8*DEFAULT_STACK_SIZE/64);
    TCB* p, *main;
    TCB::create_thread(&main, nullptr, nullptr, stack0);
    TCB::create_thread(&p, wrapperMain, nullptr, stack);

    TCB::running = main;

    TCB::yield();


    while(!userFinished) {
        TCB::yield();
    }

    __asm__ volatile("li a0, 0x0");
    __asm__ volatile("ecall");


}