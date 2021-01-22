#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include"Flags.h"

class KernelEv;

class IVTEntry {
private:
	pInterrupt old;
	KernelEv *myEvent;
	IVTNo index;
public:
	friend KernelEv;
	IVTEntry(IVTNo n, pInterrupt newInterrupt);
	virtual ~IVTEntry();
	static IVTEntry* interruptVector[255];

	void signal();
	pInterrupt getOld();
	IVTNo getIndex();
	KernelEv* getEvent();
	void callOld();
	void restoreOld();
};

#endif /* IVTENTRY_H_ */
