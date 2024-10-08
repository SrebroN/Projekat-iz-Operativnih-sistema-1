#include "../h/riscv.hpp"
#include "../lib/console.h"
#include "../h/tcb.hpp"
#include "../test/printing.hpp"
#include "../h/syscall_c.hpp"
#include "../h/memory.hpp"
#include "../h/sem.hpp"

void Riscv::handleSupervisorTrap(uint64 opCode,uint64 arg0,uint64 arg1,uint64 arg2,uint64 arg3){
    uint64 scause= r_scause();
	uint64 sepc=r_sepc();
    uint64 sstatus=r_sstatus();
    if (scause==0x0000000000000008UL || scause == 0x0000000000000009UL){
        //interrupt:no, cause code: environment call from U-mode(8) or S-mode(9)
    	uint64 ret=0;
        switch(opCode){
            case MEM_ALLOC:{
       	 		arg0*=MEM_BLOCK_SIZE;
    			ret=(uint64)MemoryAlloc::mem_alloc(arg0);
            }
            break;
            case MEM_FREE:{
                ret=(uint64)MemoryAlloc::mem_free((void*)arg0);
            }
    	 	break;
            case THREAD_CREATE:{
                ret=(uint64)TCB::createThread((thread_t*)arg0,(TCB::Body)arg1,(void*)arg2,(char*)arg3);
            }
            break;
            case THREAD_EXIT:{
                TCB::exit();
            }
            break;
            case THREAD_DISPATCH:{
                TCB::dispatch();
            }
            break;
            case SEM_OPEN:{
                ret=(uint64)Sem::createSemaphore((sem_t*)arg0,(unsigned)arg1);
            }
            break;
            case SEM_CLOSE:{
                ret=(uint64)(((sem_t)arg0)->close());
            }
            break;
            case SEM_WAIT:{
                ret=(uint64)(((sem_t)arg0)->wait());
            }
            break;
            case SEM_SIGNAL:{
                ret=(uint64)(((sem_t)arg0)->signal());
            }
            break;
            case SEM_TRYWAIT:{
                ret=(uint64)(((sem_t)arg0)->trywait());
            }
            break;
            case GETC:{
                ret=(uint64)__getc();
            }
            break;
            case PUTC:{
                char c=(char)arg0;
                __putc(c);
            }
            break;
            default:{
            }
             break;
        	}
        __asm__ volatile("mv t0, %0" : : "r"(ret));
        __asm__ volatile ("sw t0, 80(x8)");
			sepc+=4;
            w_sstatus(sstatus);
            w_sepc(sepc);
    }else if (scause==(0x01UL << 63 | 0x01)){
          //interrupt: yes, cause code: supervisor software int(timer)
        mc_sip(SIP_SSIP);
        w_sstatus(sstatus);
        w_sepc(sepc);

    }else if(scause==0x8000000000000009UL){
        //interrupt: yes, cause code: supervisor external int(console)
        console_handler();
    }else{
    printString("\nscause=");
    printInt(scause);
    printString("\nsstatus=");
    printInt(r_sstatus());
    printString("\nsepc=");
    printInt(r_sepc());
    printString("\nstval=");
    printInt(r_stval());
    while(true);
    }
}