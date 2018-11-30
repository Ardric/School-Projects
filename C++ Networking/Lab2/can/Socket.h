#ifndef SOCKET__H
#define SOCKET__H
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include "SocketSet.h"


class Socket{
public:
	bool isClosed();
	void close();
	int updateSet(fd_set* set, int max);
	int read(unsigned char* buf, int size);	
	int write( unsigned char* buf, int size);
    int readInt(int* a);
    int readDouble(double* d);
    int readString(string& str,int s);
    int writeInt(int a);
    int writeDouble(int d);
    int writeString(string str);
    
	Socket();
	void open(string host,string porto);
	Socket accept();
	void listen(string porto);
    bool hasEvent();
    void joinGroup(SocketSet* grp);
    void leaveGroup();
    string toString();
private:
	int fd;
	string host;
	string port;
	bool closed;
    SocketSet* set;
	unsigned char buffer[1024];
};

#endif
