/*
 * BlockQue.h
 *
 *  Created on: Jul 6, 2020
 *      Author: OS1
 */

#ifndef BLOCKQUE_H_
#define BLOCKQUE_H_

#include"Flags.h"
class PCB;

class BlockQueue {
public:

	BlockQueue();
	PCB* getRear();
	PCB* getFront();
	void put(PCB* pcb,unsigned timeToWait, Duration duration);
	PCB* get();
	void timePassed();
	void print();
	int getNumberOfElements();
	virtual ~BlockQueue();

private:
	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem* prev;
		unsigned blockingTime;
		Duration duration;

		Elem(PCB* p,Elem*pr=0, Elem* n=0, unsigned b, Duration d):pcb(p),prev(pr),next(n),blockingTime(b), duration(d) {}
	};
	Elem *rear, *front;
	void deleteElem(Elem* elem);
	void release();
	int numberOfElements;
};

#endif /* BLOCKQUE_H_ */
