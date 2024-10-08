#include "../h/memory.hpp"

MemoryHeader* MemoryAlloc::head;

void* MemoryAlloc::mem_alloc(size_t size){
    MemoryHeader*curr=head;

    while(curr){
        if(curr->isFree && curr->size>=size){
            curr->isFree=false;
            if(curr->size-size>=MEM_BLOCK_SIZE){

                if(!curr->next){
                    curr->next=(MemoryHeader*)(curr+size);
                    curr->next->next=nullptr;
                    curr->next->prev=curr;
                }else{
                    curr->next->prev=(MemoryHeader*)(curr+size);
                    curr->next->prev->prev=curr;
                    curr->next->prev->next=curr->next;
                    curr->next=curr->next->prev;
                }
                curr->next->isFree=true;
                curr->next->size=curr->size-size;
                curr->size=size;
            }
            break;
        }
        curr=curr->next;
    }
	if (curr==nullptr)return nullptr;
    return (void*)((uint64)curr+sizeof(MemoryHeader));
}

int MemoryAlloc::mem_free(void *arg){
    if(arg==nullptr)return 0;
    MemoryHeader*curr=head;
    arg=(void*)((uint64)arg-sizeof(MemoryHeader));
    while(curr){
        if((void*)curr==arg){
            curr->isFree=true;
            MemoryAlloc::merge_memory(curr);
            return 0;
        }
        curr=curr->next;
    }
    return -1;
}

void MemoryAlloc::merge_memory(MemoryHeader *curr){
    if(curr->next){
        if(curr->next->isFree){
            curr->size+=curr->next->size;
            curr->next=curr->next->next;
            if(curr->next){
                curr->next->prev=curr;
            }
        }
    }
    if(curr->prev){
        if(curr->prev->isFree){
            curr=curr->prev;
            curr->size+=curr->next->size;
            curr->next=curr->next->next;
            if(curr->next){
                curr->next->prev=curr;
            }
        }
    }
}

//initiate memory on heap
void MemoryAlloc::memory_init(){
	uint64 alignedAddr=(uint64)HEAP_START_ADDR;
	if (alignedAddr % MEM_BLOCK_SIZE!=0){
		alignedAddr+=MEM_BLOCK_SIZE-(alignedAddr % MEM_BLOCK_SIZE);
	}
    head=(MemoryHeader*)alignedAddr;
    head->next=nullptr;
    head->prev=nullptr;
    head->size=(uint64)HEAP_END_ADDR - (uint64)alignedAddr - 1;
    head->isFree=true;
}


