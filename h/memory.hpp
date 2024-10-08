//
// Created by os on 8/12/24.
//

#ifndef MEMORY_HPP
#define MEMORY_HPP
#include "../lib/hw.h"


struct MemoryHeader{
     MemoryHeader *next,*prev;
     size_t size;
     bool isFree;
 };

class MemoryAlloc {
public:

    static void* mem_alloc(size_t size);

    static int mem_free(void*);
    static void memory_init();
private:
    MemoryAlloc(){}

    static void merge_memory(MemoryHeader*);
    static  MemoryHeader *head;
};



#endif //MEMORY_HPP
