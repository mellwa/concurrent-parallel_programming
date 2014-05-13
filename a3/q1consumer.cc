#include "q1consumer.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;

/*****************Consumer::Consumer***********************
 Purpose: constructor of Consumer
 
 return:
 ********************************************************/
Consumer::Consumer( BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum ) : buffer(buffer), Delay(Delay), Sentinel(Sentinel), sum(sum){}


/*****************Consumer::main***********************
 Purpose: let the consumer task yield 0 - Delay-1 time
          and start to remove produce from buffer
 
 return:
 ********************************************************/
void Consumer::main(){
    int head = 0;
    do{
        yield(mprng(this->Delay - 1));//give up CPU for Delay-1 ms
        head = this->buffer.remove();
        sum += head;//calculate the sum
    }while(this->Sentinel != head);
    sum -= this->Sentinel;
}