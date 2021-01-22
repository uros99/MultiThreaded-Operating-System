#ifndef KERNELEV_H_
#define KERNELEV_H_
#include"Flags.h"
class PCB;

class KernelEv {
private:
	PCB* owner;
	int val;
	IVTNo index;
public:
	KernelEv(IVTNo index);
	PCB* getOwner();
	int getValue();
	int getIndex();
	void setOwner(PCB* pcb);
	void wait();
	void signal();
	virtual ~KernelEv();
};

#endif /* KERNELEV_H_ */
