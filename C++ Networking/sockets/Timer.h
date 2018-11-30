#ifndef TIMER__H
#define TIMER__H

#include <sys/time.h>
#include <cstdlib>

class Timer{
public:
    Timer();
    int timeLeft();
    void start(int t);
private:
    int then;
    int ttl;
    
};

#endif
