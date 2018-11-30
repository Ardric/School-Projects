CC=g++
CFLAGS=-c
LDFLAGS=
NETSRC=Socket.cpp SocketSet.cpp
SRVSRC=can.cpp Node.cpp
CLTSRC=client.cpp
NETOBJ=$(NETSRC:.cpp=.o)
SRVOBJ=$(SRVSRC:.cpp=.o)
CLTOBJ=$(CLTSRC:.cpp=.o)
SERVER=router
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
