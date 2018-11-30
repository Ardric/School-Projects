Daniel Lowdermilk, Nick Keithley, Sarah Heath
Spades Lab 4
December 1, 2017

To compile, type
	make

To run as a server, type
	./server <port number>

To run as a player, type
	./client <host name> <port number>

The RFC is located at RFC.txt.
Server code is located at backup_server.cpp
Client code is located at client.cpp

EXTRAS:
	Server does not shut down on player leaving mid-game
	or when round / game ends. Resets the game variables
	and either immediately starts a new game with already
	existing clients or waits for the lobby to refill.



Connection State

We create a Player struct which holds a socket named sock,
a string named position, a vector of Cards named Hand, a
boolean named bid, and an integer named team. The boolean
is initialized to false and turns true when a player bids
so a player is not allowed to bid more than once. The Card
struct hold the value stored as a string and a boolean named
used which is false until a player uses that card in the PLAY
state. At the beginning of main, the listener is listening
and the teams are initialized with their names set to 1 and 2
and their bids set equal to 0. Then, the listener writes a
message to the client and then is waiting for the command. 
They can either say PLYR with an argument saying which player
number they want, PLYR without an argument to get randomly 
assigned to a player, or OBSV to be an observer.

	PLYR Command
	When the client types in the PLYR command to the 
	server, we check if it has a parameter or not. If
	it does and there are no other players, they are
	automatically assigned to be player 1 and they
	are on team 1. If there are other players, the 
	server loops through and finds the next open
	player spot and assigns the team accordingly.
	If PLYR had an arguement, we try to assign them
	to that player unless it was already taken. The
	players are set into the vector of Players. The 
	server writes to the client saying either a +PLYR
	with a message with the team number and player 
	number or a - with the appropriate error message.

	OBSV Command
	The socket is then pushed back into the Observers
	vector.

	QUIT Command
	The socket is closed and does not affect any other
	clients.



Set-up State

This state is just for the server. The server will randomly
pick a player and loop through the Players vector to find
the player that matches the position of the player that
was randomly chosen. The server just takes the next card
that is in the Cards vector and gives it to the player
if the player doesn't already have 13 cards. If the
player already has all of their cards, then the server
loops through the other players and finds the next 
player with less than 13 cards and gives it to them.
The server loops through and writes a string to each
of the players telling them what their cards are. There
are no commands that the client can give during this 
state.



Bidding State

In this state, the server will ask players, in a particular order
based on the chosen dealer, what they would like to bid. It then
adds the bid to that players team bid and broadcasts what the updated
team bid is.

Once all players have bid, the server moves to the Play state.

	Acceptable commands:

	IBID

	CHAT

	QUIT



Play State

In this state, the server continues with the previous bidding order
and asks each player what card they would like to play. Once all cards
have been collected for the current trick, a check_trick function is called
to see which team gets the points for that trick.

	Acceptable commands:

	CARD

	CHAT

	QUIT



Processing State

Once all tricks have been played in a round, the server totals and broadcasts
the score for each team and decides whether the game is over or just the round.
Either way, it resets the game state to Bidding State and a new game / round is
started.

	No commands are accepted in this state
