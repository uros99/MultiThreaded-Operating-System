#include "Semaphor.h"
#include "KerneSem.h"
#include "Flags.h"

Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init);
}

int Semaphore::wait(Time maxTimeToWait){
	LOCK
	int returnValue=myImpl->wait(maxTimeToWait);
	UNLOCK
	return returnValue;
}

int Semaphore::signal(int n){
	LOCK
	int returnValue=myImpl->signal(n);
	UNLOCK
	return returnValue;
}

int Semaphore::val() const{
	return myImpl->getVal();
}

Semaphore::~Semaphore() {
	delete myImpl;
}

