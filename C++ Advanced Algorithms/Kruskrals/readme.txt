Daniel Lowdermilk, Andrew Smith

What it does:
	Reads in the description of a graph from a text file. Stores list in a vector of structs.
	Runs a sorting algorithm that orders by the weight of the edge. Loops through each edge
	and decides whether it should be added to the spanning tree vector or not.

Textfile format:
	vertices followed by weight

	ex:
		ab 3
		ac 4
		bc 1

To compile:
	g++ main.cpp

To run:
	./a.out (filename)
  	ex: ./a.out Graph2.txt
