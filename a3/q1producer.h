#ifndef _Q1PRODUCER_H_
#define _Q1PRODUCER_H_

#include "q1boundedBuffer.h"

_Task Producer {
private:
    BoundedBuffer<int> &buffer;
    const int Produce;
    const int Delay;
    void main();
public:
    Producer( BoundedBuffer<int> &buffer, const int Produce, const int Delay );
};

#endif