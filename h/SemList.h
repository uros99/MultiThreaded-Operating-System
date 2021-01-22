#ifndef SEMLIST_H_
#define SEMLIST_H_

class KernelSem;

class SemList {
private:
	struct Elem{
		KernelSem *semaphore;
		Elem* next;

		Elem(KernelSem *s,Elem* n=0):semaphore(s),next(n) {}
	};
	static Elem *head, *tail;
public:
	SemList();
	void add(KernelSem *sem);
	void timePassed();
	void print();
	virtual ~SemList();
	void deleteElem(KernelSem* sem);
};

#endif /* SEMLIST_H_ */
