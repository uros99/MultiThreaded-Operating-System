/*
 * Flags.h
 *
 *  Created on: Jul 2, 2020
 *      Author: OS1
 */

#ifndef FLAGS_H_
#define FLAGS_H_

#define LOCK asm cli
#define UNLOCK asm sti


enum ThreadState{
	BLOCKED,
	RUNNING,
	NEW,
	TERMINATED,
	READY,
	AUXTHREAD
};

enum Duration{
	UNLIMITED,
	LIMITED
};

enum TimeExpired{
	YES,
	NO
};

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

#endif /* FLAGS_H_ */
