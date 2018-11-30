// alarm.h
//
//	Data structures for managing alarms.  
//
//
//
//	By Deric Lester
//

#ifndef ALARM_H
#define ALARM_H
#include "timer.h"



class Alarm {
	public:
		Alarm(); 				

		~Alarm();				

		void wakeup();

		void GoToSleep(int time);

	private:
		int waketime;
		Semaphore* Sem;
};
#endif // ALARM_H	
