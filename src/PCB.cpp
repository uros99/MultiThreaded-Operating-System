#include "PCB.h"
#include<iostream.h>
#include"PCBList.h"
#include<dos.h>
#include"BlockQue.h"
#include "SCHEDULE.H"

PCBList PCB::listOfPCB;
ID PCB::sid=0;
PCB* PCB::running=0;
PCB* PCB::thread=0;
extern Thread* mainThread;
int PCB::brojac=0;

PCB::PCB(StackSize stackSize, Time timeSlice) {
	LOCK
	this->timeSlice=timeSlice;
	if(timeSlice==0){
		duration=UNLIMITED;
	}
	else
		duration=LIMITED;

	idPCB=sid++;
	if(stackSize>maxStackSize){
		sizeOfStack=maxStackSize;
	}
	else
		sizeOfStack=stackSize;

#ifndef BCC_BLOCK_IGNORE
	LOCK
	stackPCB=new unsigned[stackSize];
	UNLOCK

	stackPCB[stackSize - 1] = FP_SEG(myThread);
	stackPCB[stackSize - 2] = FP_OFF(myThread);
	stackPCB[stackSize - 5] = 0x200;
	stackPCB[stackSize - 6] = FP_SEG(PCB::wrapper);
	stackPCB[stackSize - 7] = FP_OFF(PCB::wrapper);
	stackSegment = FP_SEG(stackPCB + stackSize - 16);
	stackPointer = FP_OFF(stackPCB + stackSize - 16);
	basePointer = stackPointer;
#endif
	state=NEW;
	timeExpired=NO;
//	cout<<idPCB<<endl;
	blockQueue = new BlockQueue();
	listOfPCB.addPCB(this);
	UNLOCK
}

PCB* PCB::getPCB(ID id){
	return listOfPCB.getPCBbyID(id);
}

void PCB::wrapper(){
	PCB::running->myThread->run();
	PCB::running->setState(TERMINATED);
	PCB::brojac--;

	PCB* tmp;
	while((tmp=PCB::running->blockQueue->get())!=0){
		tmp->setState(READY);
		Scheduler::put(tmp);
	}

	dispatch();
}

void PCB::setState(ThreadState newState){
	state=newState;
}

void PCB::inicRunning(){
	LOCK
	mainThread=new Thread();
	inicThread();
	PCB::running=mainThread->myPCB;
	PCB::running->setState(RUNNING);
	UNLOCK
}

void PCB::infinityLoop(){
	while(1){
	}
}

void PCB::inicThread(){
	PCB::thread=new PCB(defaultStackSize,1);
//	PCB::sid--;
#ifndef BCC_BLOCK_IGNORE
	PCB::thread->stackPCB[PCB::thread->sizeOfStack - 1] = FP_SEG(PCB::thread->myThread);
	PCB::thread->stackPCB[PCB::thread->sizeOfStack - 2] = FP_OFF(PCB::thread->myThread);
	PCB::thread->stackPCB[PCB::thread->sizeOfStack - 5] = 0x200;
	PCB::thread->stackPCB[PCB::thread->sizeOfStack - 6] = FP_SEG(PCB::infinityLoop);
	PCB::thread->stackPCB[PCB::thread->sizeOfStack - 7] = FP_OFF(PCB::infinityLoop);
	PCB::thread->stackSegment = FP_SEG(PCB::thread->stackPCB + PCB::thread->sizeOfStack - 16);
	PCB::thread->stackPointer = FP_OFF(PCB::thread->stackPCB + PCB::thread->sizeOfStack - 16);
	PCB::thread->basePointer = PCB::thread->stackPointer;
#endif
	PCB::thread->setState(AUXTHREAD);
}

ThreadState PCB::getState(){
	return state;
}

Duration PCB::getDuration(){
	return duration;
}

ID PCB::getID(){
	return idPCB;
}

TimeExpired PCB::getTimeExpired(){
	return timeExpired;
}

void PCB::setTimeExpired(TimeExpired time){
	timeExpired = time;
}

PCB::~PCB() {
	LOCK
	delete blockQueue;
	delete stackPCB;
//	cout<<idPCB<<endl;
	PCB::listOfPCB.deleteElem(this);
	UNLOCK
}

