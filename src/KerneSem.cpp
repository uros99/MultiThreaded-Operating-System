#include "KerneSem.h"
#include "BlockQue.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include "SemList.h"
#include<iostream.h>

SemList* KernelSem::semList = new SemList();

KernelSem::KernelSem(int init):val(init) {
	queue = new BlockQueue();
	semList->add(this);
}

int KernelSem::abs(int n){
	if(n<0)
		return n*(-1);
	else
		return n;
}

void KernelSem::timePassed(){
	semList->timePassed();
}

int KernelSem::getVal(){
	return val;
}

int KernelSem::wait(unsigned int maxTimeToWait){
	if(--val<0){
		PCB::running->setState(BLOCKED);
		if(maxTimeToWait==0){
			queue->put(PCB::running,maxTimeToWait,UNLIMITED);
		}
		else{
			queue->put(PCB::running,maxTimeToWait,LIMITED);
		}
		dispatch();
	}

	if(PCB::running->getTimeExpired()==YES){
		PCB::running->setTimeExpired(NO);
		return 0;
	}
	else
		return 1;
}

void KernelSem::deblockThreads(int n){
	while(n>0){
		PCB* tmp = queue->get();
		if(tmp==0){
			break;
		}
		tmp->setState(READY);
		Scheduler::put(tmp);
		n--;
	}
}

int KernelSem::signal(int n){
	int returningValue=0;
	if(val<0){
		if(n>0){
			if(abs(val)<n){
				deblockThreads(val);
				returningValue=abs(val);
				val=0;
			}
			else{
				deblockThreads(n);
				returningValue=n;
				val+=n;
			}
		}
		else if(n==0){
			deblockThreads(1);
			val++;
		}
	}
	else{
		val++;
	}
	return returningValue;
}

KernelSem::~KernelSem() {
	delete queue;
	semList->deleteElem(this);
}

