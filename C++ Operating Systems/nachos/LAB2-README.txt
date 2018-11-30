Group: Group4

Members: Daniel Lowdermilk, Deric Lester, Patrick Candia

Contributions:
	Daniel:
		Established correct use of github
		Developed code for Locks, Conditions, & Thread Join
		Developed multiple test cases for Locks(2), Conditions(1), & Thread Join(1)

		Completion of these tasks involed editing the code in synch.h/cc, thread.h/cc, & threadtest.cc

		All three should be fully functional. Awaiting more test cases from group members.

	Deric:
		Helped with the development of the initial code for Lock, before it was minimalized with the
		use of semaphores.
		
		Creation and developed of the alarm.cc & alarm.h files. These files implement the GoToSleepFor(int howlong)
		function, which uses semaphores to put threads to on a wait until the clock reaches the current clock added 
		with howLong with a vector. The clock is continuously added with TimerTicks. Once the thread is sleep for 
		howLong, it is swapped to the last element of the vector and then popback is used to remove it from the list.  
		The thread associated with the alarm is then placed on the ready list.

	Patrick:
		Creation and development of two files: comm.h and comm.cc . These two files establish the Send and Recieve 
