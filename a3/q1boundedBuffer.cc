#include <vector>
#include <uC++.h>
#include <iostream>
#include "q1boundedBuffer.h"
using namespace std;

/*****************BoundedBuffer::BoundedBuffer***********************
 Purpose: constructor of BoundedBuffer
 
 return:
 ********************************************************/
template<> BoundedBuffer<int>::BoundedBuffer( unsigned int size) : size(size){
    //dynamic allocate condition and mutex locks
    this->clk_producer = new uCondLock();
    this->clk_consumer = new uCondLock();
#ifdef NOBUSY
    this->clk_barging = new uCondLock();
    this->signalFlag = false;
#endif
    this->olk = new uOwnerLock();
}


/*****************BoundedBuffer::insert***********************
 Purpose: insert elements into boundedbuffer. Done by producer
 
 return:
 ********************************************************/
template<> void BoundedBuffer<int>::insert( int elem){
    this->olk->acquire();
    
#ifdef BUSY//busy waiting
    while(bufferQueue.size() >= size){//busy waiting loop
        this->clk_producer->wait(*this->olk);
    }
#endif
    
#ifdef NOBUSY
    if(this->signalFlag){//check if the current task is a barging task
        this->clk_barging->wait(*this->olk);
        this->signalFlag = false;
    }
    if(bufferQueue.size() >= this->size){
        if(!this->clk_barging->empty()){
            this->signalFlag = true;
            this->clk_barging->signal();//wake up a task on barging lock
        }
        this->clk_producer->wait(*this->olk);
        this->signalFlag = false;//reset signal flag
    }
#endif

    assert(this->bufferQueue.size() < this->size);
    this->bufferQueue.push(elem);//insert an element into buffer
    
    if(!this->clk_consumer->empty()){
#ifdef NOBUSY
        this->signalFlag = true;
#endif
        this->clk_consumer->signal();//wake up one of the waiting consumer
    }
    else{
#ifdef NOBUSY
        if(!this->clk_barging->empty()){
            this->signalFlag = true;
            this->clk_barging->signal();
            
        }
#endif
    }
    this->olk->release();

}

/*****************BoundedBuffer::remove***********************
 Purpose: remove an element from buffer. Done by consumer
 
 return:
 ********************************************************/
template<> int BoundedBuffer<int>::remove(){
    int head;
    this->olk->acquire();
#ifdef BUSY
    while( bufferQueue.size() <= 0){//busy waiting loop
        this->clk_consumer->wait(*this->olk);
    }
#endif
    
#ifdef NOBUSY
    if(this->signalFlag){
        this->clk_barging->wait(*this->olk);//waiting on barging lock
        this->signalFlag = false;
    }
    if(bufferQueue.size() <= 0 ){
        if(!this->clk_barging->empty()){
            this->signalFlag = true;
            this->clk_barging->signal();
        }
        this->clk_consumer->wait(*this->olk);
        this->signalFlag = false;//reset signal flag
    }
#endif

    head = this->bufferQueue.front();
    assert(this->bufferQueue.size()>0);
    this->bufferQueue.pop();//remove element from buffer

    
    if(!this->clk_producer->empty()){
#ifdef NOBUSY
        this->signalFlag = true;
#endif
        this->clk_producer->signal();//wake up one of the waiting producer
    }
    else{
#ifdef NOBUSY
        if(!this->clk_barging->empty()){// if there is any task on barging lock, wake up one
            this->signalFlag = true;
            this->clk_barging->signal();
        }
#endif
    }
    this->olk->release();
    return head;
}

/*****************BoundedBuffer::~BoundedBuffer***********************
 Purpose: Destructor
 
 return:
 ********************************************************/
template<> BoundedBuffer<int>::~BoundedBuffer(){
    //deallocate locks
    delete this->clk_consumer;
    delete this->clk_producer;
#ifdef NOBUSY
    delete this->clk_barging;
#endif
    delete this->olk;
}