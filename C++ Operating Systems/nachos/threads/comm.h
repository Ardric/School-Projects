#ifndef COMM_H
#define COMM_H

#include "copyright.h"
#include "system.h"
#include "synch.h"

class Port{

  public:
    Port();
    ~Port();
    void Send(int msg);
    void Receive(int *msg);

  private:
    int value;
    Lock *mutex;
    Condition *send;
    Condition *receive;
};

Port port_obj[256];
void Send(int port, int msg);
void Receive(int port, int *msg);
#endif
