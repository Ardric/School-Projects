#include "SocketSet.h"

SocketSet::SocketSet(){
    FD_ZERO(&sockets);
    selected = sockets;
    maxFD = -1;
}


//time to wait
int SocketSet::wait(int t){
    selected = sockets;
    

    struct timeval tv;
    tv.tv_sec = t;
    tv.tv_usec = 0;
    int error = 0;
    
    if(t >= 0){
        error = select(maxFD+1, &selected,NULL,NULL,&tv);
    }else{
        error = select(maxFD+1, &selected,NULL,NULL,NULL);
    }
    return error;
}

void SocketSet::join(int fd){
    if(fd > maxFD)
        maxFD = fd;
    FD_SET(fd,&sockets);
    cout << maxFD << "\n";
}

void SocketSet::leave(int fd){
    FD_CLR(fd,&sockets);
}

bool SocketSet::isSet(int fd){
    return FD_ISSET(fd,&selected);
}