#include "q1producer.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;
/*****************Producer::Producer***********************
 Purpose: constructor of Producer
 
 return:
 ********************************************************/
Producer::Producer( BoundedBuffer<int> &buffer, const int Produce, const int Delay ) : Produce(Produce), Delay(Delay), buffer(buffer){}

/*****************Producer::main***********************
 Purpose: let the producer task yield 0 - Delay-1 time
          and start to insert produce from buffer
 
 return:
 ********************************************************/
void Producer::main(){
    for(int i = 0; i < this->Produce; i++){
        yield(mprng(this->Delay-1));
        this->buffer.insert(i+1);
    }
}