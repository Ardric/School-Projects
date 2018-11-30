A*
CMSC 262 Project 2
Fall 2015 (Blaheta)  Daniel Lowdermilk

 //Collaborated with Joshua Willis-Jones and David Lackey

To compile and run: compile Pathfinder.cpp Location.cpp
 	            ./a.out (insert name of .txt file with grid here) Example: ./a.out Grid1.txt
		    Grid options currently are Grid1.txt (Easy to get to finish)
  					       Grid2.txt (Allowed to explored a few spaces but unable
						            access finish)
					       Grid3.txt (Blocked off start, unable to explore)


Score: D-
The Program reads a text file off the command line. Opens and scans the grid in, which is then stored in
	my Pathfinder class. It then has Dijkstra's algorithm ran on it, runs without crashing and outputs
	the original grid.

Score: D
It shows the explored locations on the first grid that is printed by desplaying a "-". Also prints the original
	to show the unmodified verison for confirmation.

Score: D+
It will report if a path does or does not exist above the 1st modified printed grid.

Score: C-
It will report the length of the Path to the start if there was an actual valid path to the finish.

Score: (Rubric Stage B-, stage between C- and B- skipped)
Found path will always be the valid shortest since the current implementation


