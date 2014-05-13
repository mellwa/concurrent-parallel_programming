#ifndef _Q1BOUNDEDBUFFER_H_
#define _Q1BOUNDEDBUFFER_H_

#include <queue>
using namespace std;

template<typename T> class BoundedBuffer {
private:
    uCondLock *clk_producer;//condition lock for producer
    uCondLock *clk_consumer;
#ifdef NOBUSY
    uCondLock *clk_barging;
    bool signalFlag;
#endif
    uOwnerLock *olk;
    queue<T> bufferQueue;
    unsigned int size;
public:
    BoundedBuffer( const unsigned int size = 10 );
    void insert( T elem );
    T remove();
    ~BoundedBuffer();
};


#endif