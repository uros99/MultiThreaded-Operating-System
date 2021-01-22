#ifndef KERNESEM_H_
#define KERNESEM_H_


class BlockQueue;
class SemList;

class KernelSem {
private:
	int val;
	BlockQueue* queue;
	void deblockThreads(int n);
	static int abs(int n);
public:
	friend SemList;
	static SemList *semList;
	KernelSem(int init);
	int getVal();
	int wait(unsigned int maxTimeToWait);
	int signal(int n=0);
	static void timePassed();
	virtual ~KernelSem();
};

#endif /* KERNESEM_H_ */
