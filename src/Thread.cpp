#include "Thread.h"
#include"PCB.h"
#include"Flags.h"
#include"SCHEDULE.H"
#include<iostream.h>
#include "BlockQue.h"

extern unsigned swichOnDemand;
extern Thread *mainThread;

Thread::Thread(StackSize stackSize, Time timeSlice) {
	LOCK
	myPCB=new PCB(stackSize,timeSlice);
	myPCB->myThread=this;
	UNLOCK
}

ID Thread::getId(){
	return myPCB->getID();
}

ID Thread::getRunningId(){
	return PCB::running->getID();
}

Thread* Thread::getThreadById(ID id){
	 return PCB::getPCB(id)->myThread;
}

void Thread::start(){
	LOCK
	PCB::brojac++;
	if(myPCB->getState()==NEW){
		myPCB->setState(READY);
		Scheduler::put(myPCB);
		UNLOCK
		return;
	}
	cout<<"Exception, start method can only been called once"<<endl;
	asm cli
	UNLOCK
}
void Thread::waitToComplete(){
	LOCK
	if(myPCB->getState()!=NEW && myPCB->getState()!=TERMINATED && this!=mainThread && myPCB!=PCB::running && myPCB!=PCB::thread){
		PCB::running->setState(BLOCKED);
		myPCB->blockQueue->put(PCB::running,1,UNLIMITED);
		dispatch();
		UNLOCK
	}

}
void dispatch(){
	LOCK
	swichOnDemand=1;
	timer();
	UNLOCK
}

Thread::~Thread() {
	LOCK
	delete myPCB;
	UNLOCK
}

