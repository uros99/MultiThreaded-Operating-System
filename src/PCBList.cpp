#include "PCBList.h"
#include"PCB.h"

PCB* PCBList::getPCBbyID(int id){
	if(head==0)return 0;
	Elem* tmp;
	for(tmp=head;tmp!=0;tmp=tmp->next)
		if(tmp->pcb->getID()==id)
			return tmp->pcb;
	return 0;
}

void PCBList::deleteElem(PCB *p){
	if(head->pcb==p){
		Elem *old = head;
		head = head->next;
		delete old;
		return;
	}
	Elem *prev=head;
	Elem *curr=head->next;
	while(curr->pcb!=p){
		prev = curr;
		curr = curr->next;
	}
	if(tail->pcb==curr->pcb)
		tail = prev;
	prev->next=curr->next;
	delete curr;
}

PCBList::~PCBList() {
	while(head!=0){
		Elem *old=head;
		head=head->next;
		delete old;
	}
}

