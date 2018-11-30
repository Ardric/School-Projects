// alarm.cc
//	Using a hardware timer device to provide an
//	alarm clock.
//
//
//	By Deric Lester

#include "alarm.h"
#include <vector>
#include "timer.h"


void GoToSleep(int howLong);
Timer *alarmTimer = new Timer(wakeup,0,false);
std::vector<Alarm*> alarms;
int clock = 0;
//------------------------------------------------------------
//Alarm::Alarm
//
//
//-------------------------------------------------------------
Alarm::Alarm()
{
	Sem = new Semaphore("Alarm", 0);
	//t = currentThread;   			
}
//---------------------------------------------------------------
//Alarm::~Alarm
//
//	
//--------------------------------------------------------------

Alarm::~Alarm()
{
	delete Sem;
}



//---------------------------------------------------------------
//GoToSleepFor(int howLong)
//
//
//
//
//
//----------------------------------------------------------------

void Alarm::GoToSleep(int howLong)
{
	Alarm* a = new Alarm;
        alarms.push_back(a); 	
	a->waketime = (clock + howLong);
	Sem->P();
}

void Alarm::wakeup()
{
	clock += Timerticks;
	for(auto a : Alarms)
	{
		if(clock >= a->waketime)
		{
			Sem->V();
			alarms.swap(alarms[a], alarms[alarms.size() - 1]);
			alarms.pop_back();
			//t.setStatus()->READY;
		}


	}



}
