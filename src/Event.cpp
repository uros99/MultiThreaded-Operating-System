#include "Event.h"
#include "KernelEv.h"
#include "Flags.h"

Event::Event(IVTNo ivtNo) {
	LOCK
	myImpl = new KernelEv(ivtNo);
	UNLOCK
}

void Event::signal(){
	LOCK
	myImpl->signal();
	UNLOCK
}

void Event::wait(){
	LOCK
	myImpl->wait();
	UNLOCK
}

Event::~Event() {
	LOCK
	delete myImpl;
	UNLOCK
}

