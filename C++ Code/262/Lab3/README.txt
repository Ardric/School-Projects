Spamassassin
CMSC Project 3
Fall 2015 (Blaheta) Daniel Lowdermilk

To compile and run: compile REWORKEDSpamassassin.cpp
		    ./a.out whatever pathname you want as long as the file you end up in has an index in it.

Score: D-
To run the prep option 
	./a.out (insert path here) prep

Score: D
To see that it calculates total number of words in message bodies
	./a.out (insert path here) count

Score: D+
To see that it gathers word counts separately for each distinct word
	./a.out (insert path here) distinctcount

Score: C
Gathers word count separately for ham and spam
	./a.out (insert path here) maps

Score: C+
Word counts frequency of documents containing words rather than overall frequency
	handled in distinctcount

Score: B-
To run the single option
	./a.out (insert path here) single

Score: B
Accounts for unknown words
	handled in single

Score: B+
Accounts for empirically zero probabilities
	handled in single

Score: B+
Combines all conditional terms with prior to give classification for individual email
	handled in single

Score: A-
Prevent arithmatic underflow
	handled in single
