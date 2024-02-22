//
// Created by os on 8/1/22.
//

#ifndef PROJECT_BASE_V1_1_QUEUE_HPP
#define PROJECT_BASE_V1_1_QUEUE_HPP

#include "../test/printing.hpp"
#include "MemoryAllocator.hpp"

template<typename T>
class Queue {

    struct Elem {
        T* data;
        Elem* next;

        Elem(T* data, Elem* next) : data(data), next(next) {}
        void* operator new(uint64 n) {
            uint64 sizeInBlocks = n / MEM_BLOCK_SIZE;
            if (sizeInBlocks * MEM_BLOCK_SIZE < n ) sizeInBlocks += 1;
            return MemoryAllocator::mem_alloc(sizeInBlocks);
        }

        void operator delete(void* p) {
            MemoryAllocator::mem_free(p);
        }

    };

    Elem* head, *tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    Queue(const Queue<T>&) = delete;
    Queue<T> operator=(const Queue<T>&) = delete;

    ~Queue<T>() {
        Elem* old = nullptr;
        while (head) {
            old = head;
            head = head->next;
            delete old;
        }
    }

    void* operator new(uint64 n) {
        //printString("queue->new\n");
        uint64 sizeInBlocks = n / MEM_BLOCK_SIZE;
        if (sizeInBlocks * MEM_BLOCK_SIZE < n ) sizeInBlocks += 1;
        return MemoryAllocator::mem_alloc(sizeInBlocks);
    }

    void operator delete(void* p) {
        MemoryAllocator::mem_free(p);
    }


    //add last
    void add(T* data) {
        if (!data) return;
        Elem* elem = new Elem(data, nullptr);

        if (tail) {
            tail->next = elem;
            tail = elem;
        }
        else {
            head = tail = elem;
        }
    }

    //remove first
    T* remove() {
        if (!head) return nullptr;

        Elem* elem = head;
        head = head->next;
        if (!head) tail = nullptr;

        elem->next = nullptr;
        T* data = elem->data;
        delete elem;
        return data;
    }

    //peek first
    T* peek() {
        if (!head) return nullptr;
        return head->data;
    }

    void addFirst(T* data) {
        if (!data) return;
        Elem* elem = new Elem(data, nullptr);
        elem->next = head;
        head = elem;
        if (!tail) tail = elem;
    }

    T* next(T* data) {
        if (!data) return nullptr;
        Elem* elem = head;
        while (elem && elem->data != data) elem = elem->next;
        if (!elem) return nullptr;
        if (!elem->next) return nullptr;
        else return elem->next->data;
    }

    void addAfter(T* previousData, T* data) {
        if (previousData == nullptr || data == nullptr) return;
        Elem* previous = head;
        while (previous && previous->data != previousData) previous = previous->next;
        Elem* elem = new Elem(data, nullptr);
        if (!previous) return;
        elem->next = previous->next;
        previous->next = elem;
        if (!elem->next) tail = elem;
    }
};


#endif //PROJECT_BASE_V1_1_QUEUE_HPP
