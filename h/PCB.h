#ifndef PCB_H_
#define PCB_H_

#include"Thread.h"
#include"Flags.h"

#define maxStackSize 65535
class PCBList;
class BlockQueue;

class PCB {
private:
	static ID sid;
	ID idPCB;
	ThreadState state;
	Duration duration;
	TimeExpired timeExpired;
	static void inicThread();
public:

	unsigned stackPointer;
	unsigned stackSegment;
	unsigned basePointer;
	unsigned *stackPCB;
	Time timeSlice;
	static PCBList listOfPCB;
	static PCB* running;
	static PCB* thread;
	Thread *myThread;
	StackSize sizeOfStack;
	BlockQueue *blockQueue;

	PCB(StackSize stackSize, Time timeSlice);
	virtual ~PCB();
	ID getID();
	ThreadState getState();
	Duration getDuration();
	TimeExpired getTimeExpired();
	void setTimeExpired(TimeExpired time);
	static void wrapper();
	static PCB* getPCB(ID id);
	static void inicRunning();
	static void infinityLoop();
	void setState(ThreadState newState);

	static int brojac; //provera
};

#endif /* PCB_H_ */
