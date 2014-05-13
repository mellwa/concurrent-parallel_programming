#include "q1boundedBuffer.h"
#include "q1producer.h"
#include "q1consumer.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

MPRNG mprng(getpid());


/*****************uMain::main***********************
 Purpose: run the program, handle the invalid arguments
          create number of consumers and producers to
          insert/remove element into/from boundedbuffer
 
 return:
 ********************************************************/
void uMain::main(){
    int sum = 0;
    int i,j;
    //default value of arguments
    int cons = 5;
    int prods = 3;
    int produce = 10;
    int bufferSize = 10;
    int delays;
    switch (argc) {
        case 6:
            delays = atoi(argv[5]);
        case 5:
            bufferSize = atoi(argv[4]);
        case 4:
            produce = atoi(argv[3]);
        case 3:
            prods = atoi(argv[2]);
        case 2:
            cons = atoi(argv[1]);
        case 1:
            break;
        default:
            cerr<<"Usage: "<<argv[0]<<" [ Cons (> 0) [ Prods (> 0) [ Produce (> 0) [ BufferSize (> 0) [ Delay (> 0) ] ] ] ] ]"<<endl;
            uRetCode = 0;
            return;
    }
    delays = cons+prods;
    
    if(cons <=0 || prods<=0 || produce<=0 || bufferSize<=0 || delays<=0){
        cerr<<"Usage: "<<argv[0]<<" [ Cons (> 0) [ Prods (> 0) [ Produce (> 0) [ BufferSize (> 0) [ Delay (> 0) ] ] ] ] ]"<<endl;//print out usage message
        uRetCode = 0;
        return;
    }
    
    
    
#ifdef __U_MULTI__
    uProcessor p[3] __attribute__(( unused )); // create 3 kernel thread for a total of 4
#endif // __U_MULTI__
    
    BoundedBuffer<int> *bb = new BoundedBuffer<int>(bufferSize);
    Producer *prod[prods];
    Consumer *con[cons];
    for(i = 0; i < prods; i++)
        prod[i] = new Producer(*bb,produce,delays);//create producer task
    
    for(j = 0; j < cons; j++)
        con[j] = new Consumer(*bb,delays,-1,sum);//create consumer task
    
    for(i = 0; i<prods;i++){
        delete prod[i];
    }
    for(i = 0; i<cons;i++){
        bb->insert(-1);
    }
    for(j = 0; j < cons; j++){
        delete con[j];
    }

    cout<<"total: "<<sum<<endl;
    delete bb;
}
