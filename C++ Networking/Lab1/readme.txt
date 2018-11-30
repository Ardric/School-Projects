Daniel Lowdermilk - Nick Keithley

Compilation:
	g++ Main.cpp
	./a.out filename.txt

Explanation of code:
	Takes in bits from a file and inserts them into buffer.
	Loops through buffer getting the byte value of every 8 consecutive bits
	Treats a space as 1 byte
	Prints out contents of vector when it is filled with 4 bytes (simulating how much we can send with whiteboard) as hex
  	When input has finished being processed it prints out the incomplete final frame as hex.

Analysis of maximum bits per second:
	Since 32 bits are sent every 45 seconds our max bits per seconds are 0.71 bps.

	Nyquist: Sending as many signals through the channel as its bandwidth will allow. Since we've set the clock to be
		 45 seconds and the max bits we send to 32 bits (because of whiteboard space), we are limited to sending 
		 data at 0.71 bps. However, because we are working in a visual channel, we could potentially send a lot 
		 more data at a time if we used something like, say, a bigger whiteboard.

	Shannon: Says with nothing blocking our path (visually) that at most we can send 0.71 bps. Where if we had "noise"
		 blocking half our path (visually imparing 50% of the whiteboard) we could only send 0.35 bps.
