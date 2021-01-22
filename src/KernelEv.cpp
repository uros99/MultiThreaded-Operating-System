#include "KernelEv.h"
#include "PCB.h"
#include "IVTEntry.h"
#include "SCHEDULE.H"

KernelEv::KernelEv(IVTNo index) {
	this->index=index;
	owner=PCB::running;
	IVTEntry::interruptVector[index]->myEvent=this;
}

PCB* KernelEv::getOwner(){
	return owner;
}

int KernelEv::getValue(){
	return val;
}

void KernelEv::setOwner(PCB* pcb){
	owner = pcb;
}

void KernelEv::signal(){
	if(owner == 0){
		val=1;
	}
	else{
		owner->setState(READY);
		Scheduler::put(owner);
		owner=0;
	}
}

void KernelEv::wait(){
	if(owner == PCB::running){
		if(val == 1)
			val=0;
		else{
			PCB::running->setState(BLOCKED);
			owner = PCB::running;
			dispatch();
		}
	}
}

KernelEv::~KernelEv() {
	if(owner!=0){
		owner->setState(READY);
		Scheduler::put(owner);
		owner=0;
	}
	IVTEntry::interruptVector[index]->callOld();
	IVTEntry::interruptVector[index]->restoreOld();
	IVTEntry::interruptVector[index]=0;
}

