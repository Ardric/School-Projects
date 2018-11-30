Daniel Lowdermilk
12/1/2015
CMSC 262
Lab4: Registrar

// The three functions at the top of my main file which handle my sql statements are from http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm




To compile:
	compile sqlite.cpp -lsqlite3

To run:
	./a.out database.db option
		Three options:
			student (If you are a student looking at classes and registering for classes).
			teacher (If you are a teacher trying to see the list of classes you are teaching).
			registrar (If you would like to add students, teachers or classes to the database, or if you would like to
			    		delete something from a table or update an existing table.)

Ideally, how this runs is the registrar will add students, teachers and classes to the database.  Once a student or teacher has been
added to the database, they will be allowed to access certain tables and perform certain tasks.  However, currently there is no error
checking so you can log in as a student not registered and sign up for classes as long as you provide a name and ID.  Also once a request 
is complete it closes and you have to run it again to do another request. There are preloaded students, classes and teachers.  If you want
to view these tables without logging into sqlite3 itself, log in as the registrar and go to update tables. Select the table you want and it 
will show you what is in the existing table. There is other obvious error checking I've missed throughout this but it will work as intended.
I do not have it able to keep track of cap size or if classes conflict.

Rubric:
D-	Prep Work completed.

D	Clean schema, only tables not connected are students to classes which would be connected if teachers were able to see students in their
	classes.

D+	If you log in as a student you can see all classes based on term.  (Currently the only terms supported are Fall and Spring 2017.
    	So if you add a class have it under one of those two terms please.)

D+	If you log in as a student you can see all classes from a particular department. (Currently the only departments supported are the
    	ones in the database, same situation as the above bullet point.)

C-	If you log in as a student you can see all classes taught by a particular professor. You can also log in as a teacher and see the 
        samething. (Same situation as the bullet points above)

 	(All three situations above can be made flexible by changing it to a string to accept user input and sending it to the str_to_constptr
	 function.  You will see where this is already implemented further in the program.  Based on time contraint leaving this section as is
	 instead of updating.)

C	If you log in as the registrar you will be able to add items to each table.

B-	If you log in as the registrar you will be able to modify existing data in tables and delete from tables.
	You will delete students and teachers based on their ID. You will be able to modify everything except, studentID, teacherID, class section
	and department.

B-	Easy to update and check the database that updates have been made.

B	If you log in as a student you have the option to show classes based on schedule and period

B+	If you log in as a student you have the option to register for classes.  You must create a schedule based off your name and student ID
	that are in the student table. Once you have created your schedule you can register for classes based off CRN that will be added to your
	schedule.

B+	If you log in as a student you have the option to view the schedule table you have created.

A+ 	(Just the last thing on the rubric.) Completed three complex queries.



