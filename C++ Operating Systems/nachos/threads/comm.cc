//#ifndef COMM_H
//#define COMM_H

#include "copyright.h"
#include "system.h"
#include "synch.h"
#include "comm.h"


Port::Port()
{
  mutex = new Lock("mutex");
  send = new Condition("send");
  receive = new Condition("receive");
}
Port::~Port()
{
  delete mutex;
  delete send;
  delete receive;
}

void Port::Send(int msg)
{
  mutex->Acquire();
  value = msg;
  receive->Signal(mutex);
  send->Wait(mutex);
  mutex->Release();
}

void Port::Receive( int* msg)
{
  mutex->Acquire();
  send->Signal(mutex);
  receive->Wait(mutex);
  *msg = value;
  mutex->Release();
}
void Send(int port, int msg)
{
  if(port > 255 || port < 0)
    return;
  port_obj[port].Send(msg);
}
void Receive(int port, int *msg)
{
  if(port > 255 || port < 0)
    return;
  port_obj[port].Receive(msg);


}
//#endif
