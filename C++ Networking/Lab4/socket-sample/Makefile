CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lncurses
NETSRC=Socket.cpp SocketSet.cpp
SRVSRC=backup_server.cpp Timer.cpp
CLTSRC=client.cpp Console.cpp
NETOBJ=$(NETSRC:.cpp=.o)
SRVOBJ=$(SRVSRC:.cpp=.o)
CLTOBJ=$(CLTSRC:.cpp=.o)
SERVER=server
CLIENT=client

all: $(SERVER) $(CLIENT)

$(SERVER): $(NETOBJ) $(SRVOBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(CLIENT): $(NETOBJ) $(CLTOBJ)
	$(CC) $(LDFLAGS) $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:	
	rm -f *.o $(SERVER) $(CLIENT) 
	touch *
