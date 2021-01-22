#ifndef PCBLIST_H_
#define PCBLIST_H_

class PCB;

class PCBList{
private:
	struct Elem{
		PCB* pcb;
		Elem* next;

		Elem(PCB *p, Elem* n):pcb(p),next(n){}
	};
	Elem* head,*tail;
	Elem* curr;
public:
	PCBList(){head=tail=curr=0;}
	PCB* getHead(){return head->pcb;}
	PCB* getTail(){return tail->pcb;}
	PCB* getCurr(){return curr->pcb;}
	PCB* getPCBbyID(int id);

	void addPCB(PCB *p){
		if(head==0){
			head=tail=new Elem(p,0);
		}
		else{
			tail->next=new Elem(p,0);
			tail=tail->next;
		}
	}
	void deleteElem(PCB *p);
	~PCBList();
};

#endif /* PCBLIST_H_ */
