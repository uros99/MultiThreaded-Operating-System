#ifndef EVENT_H_
#define EVENT_H_
#include"IVTEntry.h"
#include "Flags.h"
#define PREPAREENTRY(numEntry, callOldRout) \
		void interrupt inter##numEntry(...); \
		IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
		void interrupt inter##numEntry(...) { \
			newEntry##numEntry.signal(); \
			if (callOldRout == 1) \
			newEntry##numEntry.callOld(); \
}


typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();
	void wait ();
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
 KernelEv* myImpl;
};

#endif /* EVENT_H_ */
