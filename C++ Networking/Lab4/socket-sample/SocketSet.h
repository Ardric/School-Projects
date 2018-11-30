#ifndef SOCKETSET__H
#define SOCKETSET__H
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
#include <iostream>
#include <string>


using namespace std;

class SocketSet{
public:
    SocketSet();
    int wait();
    int wait(int t);
    void join(int fd);
    void leave(int fd);
    bool isSet(int fd);
private:
	int maxFD;
    fd_set sockets;
    fd_set selected;
};

#endif
