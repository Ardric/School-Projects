Daniel Lowdermilk

Join:
	Can handle one node joining. The node that join correctly gets coordinate ownership from node it split from.
	Both nodes correctly update peeps table and can communicate.

Leave:
	Not working

Set:
	Able to Set values within coordinate ownernship. Will pass the request to neighbor or return out of bounds
	request if original node is unable to satisfy request.

Get:
	Able to Get values within coordinate ownership. Will pass the request to neighbor or return out of bounds
	request if original node is unable to satisfy request.

Display:
	Able to correctly print out ownership of coordinates in a 10x10 grid that increments its sections by 0.099
	on the x-axis and .100 on the y.
	Print can be called on either node and correctly display ownership.
	Will cause the client to exit so client will have to be reran.




Limitations:
	Not able to share hashtable values to joining node if they were already set in it coordinates.
	Join not in a position to handle more than 1 note (undefined behaviour if attempted).





How to compile:
	make

How to run:
	./router (port)
  		to join: ./router (port) (IP of router to join) (port of router to join)
	
	./client (IP of router to join) (port of router to join)
  		Print <--Prints out ownership on server(not sent back to client)
  		Get x.xxx y.yyy <--Gets a value at specified location
		Set x.xxx y.yyy value <--Sets a value at specified location
