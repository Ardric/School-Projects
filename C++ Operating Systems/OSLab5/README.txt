Group4:
	Daniel Lowdermilk, Patrick Candia, Deric Lester

Individual Tasks:
	Deric: N/A
	Patrick: N/A
	Daniel: Implemented external defragmentation. Created two
		functions, one that detects external fragmentation
		and one that corrects external fragmentation.

		The first function can correctly test for external fragmentation.
		The second function however has a weird bug with its recursion
		that causes it to not correctly fix external fragmentation.

Testing external defragmentation functions:
	g++ filesys.cpp operations.cpp test.cpp

	./a.out

	Runs a test case where 3 files are created, checks if there is fragmentation,
	deletes a file, checks for fragmentation again, then trys to correct fragmentation
	then checks one last time.
