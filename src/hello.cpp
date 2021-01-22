#include <iostream.h>
#include"Thread.h"
#include"PCB.h"
#include"SCHEDULE.H"
#include"BlockQue.h"
#include"Semaphor.h"

Thread* mainThread;

extern int userMain(int argc, char* argv[]);

void main(int argc, char *argv[])
{
	inic();
	userMain(argc,argv);
	restore();
}
