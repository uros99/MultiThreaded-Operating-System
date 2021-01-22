/*
 * BlockQue.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: OS1
 */

#include "BlockQue.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include<iostream.h>
BlockQueue::BlockQueue(){
	rear=front=0;
	numberOfElements=0;
}

void BlockQueue::put(PCB* pcb, unsigned timeToWait, Duration duration){
	Elem* tmp = new Elem(pcb,0,0,timeToWait,duration);
	if(rear==0){
		rear=front=tmp;
	}
	else{
		rear->prev=tmp;
		tmp->next=rear;
		rear=tmp;
	}
	numberOfElements++;
}

PCB* BlockQueue::get(){
	if(front!=0){
		if(front == rear) rear=0;
		PCB* pcb=front->pcb;
		Elem *tmp = front->prev;
		front->prev=0;
		front->pcb=0;
		front->next=0;
		if(tmp!=0)
			tmp->next=0;
		delete front;
		front = tmp;
		numberOfElements--;
		return pcb;
	}
	return 0;
}

int BlockQueue::getNumberOfElements(){
	return numberOfElements;
}

PCB* BlockQueue::getRear(){
	return rear->pcb;
}

PCB* BlockQueue::getFront(){
	return front->pcb;
}

void BlockQueue::deleteElem(Elem *elem){
	if(elem==rear)
		rear=rear->next;
	else if(elem==front){
		front=front->prev;
	}

	Elem *prevElem=elem->prev;
	Elem *nextElem=elem->next;


	if(prevElem!=0)
		prevElem->next=nextElem;
	if(nextElem!=0)
		nextElem->prev=prevElem;

	elem->prev=0;
	elem->next=0;
	elem->pcb=0;
	delete elem;
}

void BlockQueue::timePassed(){
	Elem *head=rear;
	while(head!=0){
		if(head->duration==LIMITED){
			head->blockingTime--;
			if(head->blockingTime==0){
				head->pcb->setState(READY);
				head->pcb->setTimeExpired(YES);
				Scheduler::put(head->pcb);
				Elem *old=head;
				head=head->next;
				deleteElem(old);
			}
			else{
				head=head->next;
			}
		}
		else{
			head=head->next;
		}
	}
}

void BlockQueue::print(){
	cout<<"USAO U PRINT"<<endl;
	Elem *tmp=rear;
	while(tmp){
		cout<<tmp->blockingTime<<" ";
		tmp = tmp->next;
	}
	cout<<endl;
}
void BlockQueue::release(){
	while(rear!=0){
		Elem *old = rear;
		rear = rear->next;
		PCB *pcb = old->pcb;
		pcb->setState(READY);
		Scheduler::put(pcb);
		delete old;
	}
}
BlockQueue::~BlockQueue() {
	release();
}

