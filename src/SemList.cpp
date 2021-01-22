#include "SemList.h"
#include "KerneSem.h"
#include "BlockQue.h"
#include<iostream.h>
#include"Flags.h"


SemList::Elem* SemList::head=0;
SemList::Elem* SemList::tail=0;

SemList::SemList() {
}
void SemList::add(KernelSem* sem){
	if(head==0){
		head=tail=new Elem(sem,0);
	}
	else{
		tail->next=new Elem(sem,0);
		tail=tail->next;
	}
}
void SemList::timePassed(){
	Elem *tmp;
	for(tmp=head;tmp!=0;tmp=tmp->next){

		tmp->semaphore->queue->timePassed();
	}
}

void SemList::print(){
	Elem *tmp = head;
	while(tmp){
		tmp->semaphore->queue->print();
	}

}

void SemList::deleteElem(KernelSem *sem){
	if(head==0) return;
	if(head->semaphore==sem){
		Elem *old = head;
		head = head->next;
		delete old;
		return;
	}

	Elem *prev = head;
	Elem *curr = head->next;
	while(curr->semaphore!=sem){
		prev = curr;
		curr = curr->next;
	}
	if(tail->semaphore==curr->semaphore)
		tail = prev;
	prev->next = curr->next;
	delete curr;
}

SemList::~SemList() {

	while(head!=0){
		Elem *old=head;
		head=head->next;
		delete old;
	}
}

