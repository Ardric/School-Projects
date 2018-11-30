group4: Daniel Lowdermilk, Deric Lester, Patrick Candia

	Task 2: Implemented Create, Open, Close, Read, Write
	All code for system call and handler functions are located in exception.cc

		Create: Takes in a filename provided by the user. Reads in the name with the use
			of a helper function that used ReadMem to access the data in register 4 and utilized
		
		Open:  Takes in a filename provided by the users, which is read by a helper function to convert
			it to a kernel string.  The filename is then opened a placed in a unique FileTable position.

		Close:  Takes in a filename provided by the users, which is read by a helper function to convert 
			it to a kernel string.  The FileTable postion of the file is converted to a null pointer
			to allow future files to claim the postion.  And then the filename is deleted.

		Read:  Takes in a buffer, a size of buffer variable, and location to read from (can be a file or consoleInput).
			Once it has decided where it's going to read from, (0 = consoleInput, or filename), it passes a kernel_str
			variable, buffer parameters and the place it wants to read from to a function that reads the contents of the
			console or file up to variable size amount and places it into a kernel_str. It then moves the contents of the
			kernel_str to the buffer through a char* temp variable that allows communication between userspace and kernel space
			with the function WriteMem.

		Write: Takes in a buffer, a size of buffer variable, and a location to write to (can be a file or consoleOutput).
			Once it has decided where it's going to write to, (1 = consoleOutput, or filename), it passes a kernel_str
			variable, buffer parameters, and the place it wants to write to to a function that writes the contents of the 
			buffer or the file, up to variable size amount, to a file or consoleOutput.

	Task 3: SynchConsole utilizes the functions already implemented in console.  SynchConsole ensures that the console is locked everytime a thread is using it.
		This ensures that a thread finishes its read/write before another starts.  SynchConsole also waits until a read is available or a write is done.

	Task 4: Implemented Exec, join and exit.
	All code located in exception.cc
		
		Exec: Takes a NachOS formatted executable file that is to be ran by the forked process. Reads this in from userspace by using the
			same functions as read. Creates a new thread and forks that thread off to a function named StartProcess with the executable file
			name to be ran. In StartProcess, the thread has an address space created for it and then runs the file passed with it.

		Join: Takes an address space id that identifies the thread we are waiting on. Uses the id to identify the thread via lookup in our processID array.
			Then calls thread->join on the identified process and writes the return status placed in its array position from thread->finish (Exit system call).

		Exit: Takes a status that is to be put in the currentThreads slot in the processID array indiciating how it exited. thread->Finish() is called
			then the status is placed in the array.

	Individual Tasks:
		Daniel: Task 7
			Currently when the Yield system call is called, it tells the current thread to yield
			Fork is not implemented.

		Patrick: N / A
			Did not work on a individual task

		Deric: Task 6
			The idea behind cat.c is to read from the console input and retrieve the first file and a second file if one is there.
			It then attempts to open both of the files, and checks to see if either of the files are unavailable.  If the first file is NULL
			then we know there is no file to receive info from, so we tell the user the proper structures for the cat command.  If the writeFrom
			is NULL then we create a new file with the name specified.  Reopen the file and write the info from the first file into it.  Else we 
			just print out the information to the console.
			
			Cp is the same thing as cat file.txt file2.txt.  We read in the contents from file.txt and write them to file2.txt.  The only difference 
			is there is no handling of info to print to console.  cp needs to inputs from the user, so it knows where to write the contents of the read.

			cp and cat are untested because implementing them into the makefile wouldn't work.

	Contributions to group work:	
		Daniel:
			Task 2: Wrote the code and test cases for Create, Open, Close, Read, Write
			Task 3: Wrote the code and test cases for synchconsole.h & synchconsole.cc
			Task 4: Wrote the code for Exec, exit and join, though exit and join.

		Patrick:
			Task 2: Participated in discussion about the logic behind system call implementation
			Task 3: Read about the task but didn't contribute to implementation (was working on test cases for task 2 systemcalls,
			    	however, was unable to get test cases to compile.)
			Task 4: Went home before implementation

		Deric: 
			Task 2: Contributed to the implementation of Create, Close, Open, Read and created the Program counter to make sure System calls don't infinetly call.
			Task 3: Contributed to the implementation of synchconsole.h & synchconsole.cc
			Task 4: Contributed to the implementation of exec, and partial, nonworking code of exit and join.
