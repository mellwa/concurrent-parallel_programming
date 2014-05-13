#ifndef _Q1CONSUMER_H_
#define _Q1CONSUMER_H_

#include "q1boundedBuffer.h"

_Task Consumer {
private:
    BoundedBuffer<int> &buffer;
    int Delay;
    int Sentinel;
    int &sum;//the reference of sum
    void main();
public:
    Consumer( BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum );
};

#endif