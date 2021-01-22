#include "IVTEntry.h"
#include<DOS.h>
#include "KernelEv.h"
IVTEntry* IVTEntry::interruptVector[255];

IVTEntry::IVTEntry(IVTNo n, pInterrupt newInterrupt){
	if(n<255){
		interruptVector[n] = this;
		index = n;
#ifndef BCC_BLOCK_IGNORE
		old = getvect(n);
		setvect(n,newInterrupt);
#endif
		myEvent = 0;
	}
}

KernelEv* IVTEntry::getEvent(){
	return myEvent;
}

void IVTEntry::callOld(){
	if(old!=0)
		old();
}

void IVTEntry::restoreOld(){
	if(old!=0){
#ifndef BCC_BLOCK_IGNORE
		setvect(index, old);
		old=0;
#endif
	}
}

pInterrupt IVTEntry::getOld(){
	return old;
}

IVTNo IVTEntry::getIndex(){
	return index;
}

void IVTEntry::signal(){
	if(myEvent!=0)
		myEvent->signal();
}

IVTEntry::~IVTEntry() {
	//callOld();
//	restoreOld();
	interruptVector[index]=0;
}

