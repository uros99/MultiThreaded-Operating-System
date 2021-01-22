#include"PCB.h"
#include"Flags.h"
#include"SCHEDULE.H"
#include"Timer.h"
#include<iostream.h>
#include "KerneSem.h"
#include "SemList.h"
#include"DOS.h"
volatile unsigned tmpSS,tmpSP,tmpBP;
volatile unsigned runningQuantum=0;
unsigned swichOnDemand;
unsigned oldTimerOff, oldTimerSeg;
extern Thread* mainThread;
extern void tick();

void interrupt timer(...) {
	if(!swichOnDemand && PCB::running->getDuration()==LIMITED && runningQuantum!=0){
		runningQuantum--;
	}
	if(runningQuantum==0 || swichOnDemand==1){
		asm{
			mov tmpSP, sp
			mov tmpSS, ss
			mov tmpBP, bp
		}

		PCB::running->stackPointer = tmpSP;
		PCB::running->stackSegment = tmpSS;
		PCB::running->basePointer = tmpBP;

		if(PCB::running->getState()==RUNNING) {
			PCB::running->setState(READY);
			Scheduler::put(PCB::running);
		}

		PCB::running = Scheduler::get();
		if(PCB::running!=0){
			PCB::running->setState(RUNNING);
		}
		else{
			PCB::running=PCB::thread;
		}

		tmpSP = PCB::running->stackPointer;
		tmpSS = PCB::running->stackSegment;
		tmpBP = PCB::running->basePointer;

		runningQuantum = PCB::running->timeSlice;

		asm{
			mov sp, tmpSP
			mov ss, tmpSS
			mov bp, tmpBP
		}

	}
	if(!swichOnDemand){
		KernelSem::timePassed();
		tick();
		asm int 60h;
	}
	swichOnDemand=0;
}

void inic(){
	LOCK
		asm{
				cli
				push es
				push ax

				mov ax,0
				mov es,ax

				mov ax, word ptr es:0022h
				mov word ptr oldTimerSeg, ax
		    	mov ax, word ptr es:0020h
				mov word ptr oldTimerOff,ax

				mov word ptr es:0022h, seg timer
				mov word ptr es:0020h, offset timer

				mov ax, oldTimerSeg
				mov word ptr es:0182h, ax
				mov ax, oldTimerOff
				mov word ptr es:0180h, ax

				pop ax
				pop es
				sti
			}
		PCB::inicRunning();
		UNLOCK
}

void restore(){
/*	LOCK
	#ifndef BCC_BLOCK_IGNORE
		pInterrupt oldRoutine = getvect(0x60);
		setvect(0x8, oldRoutine);
	#endif*/
#ifndef BCC_BLOCK_IGNORE
	LOCK
	asm {

			 push es
			 push ax
			 mov ax,0
			 mov es,ax
			 mov ax, word ptr oldTimerSeg
			 mov word ptr es:0022h, ax
			 mov ax, word ptr oldTimerOff
			 mov word ptr es:0020h, ax
			 pop ax
			 pop es

	 }
	UNLOCK
	 #endif

	delete mainThread;
	delete PCB::thread;
	UNLOCK
}
