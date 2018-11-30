#include "Timer.h"

Timer::Timer(){
    then = 0;
    ttl = 0;
}

void Timer::start(int t){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    then = tp.tv_sec;
    ttl = t;
}

int Timer::timeLeft(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    int now = tp.tv_sec;
    now -= then;
    int t = ttl - now;
    if(t < 0)
        t = 0;
    return t;
}

