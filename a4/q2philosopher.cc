#include "q2philosopher.h"
#include "q2printer.h"
#include "MPRNG.h"
using namespace std;

extern MPRNG mprng;

/*****************Philosopher::Philosopher***********************
 Purpose: constructor.
 
 return:
 ********************************************************/
Philosopher::Philosopher( unsigned int id, unsigned int noodles, Table &table, Printer &prt ) : id(id), noodles(noodles), table(table), printer(prt){
    
}

/*****************Philosopher::main***********************
 Purpose: the performance of a philosopher
            - hungry message
            - yield a random number of times, between 0 and 4
            inclusive, to simulate the time to get hungry
            - pickup forks
            - pretend to eat a random number of noodles,
            between 1 and 5 inclusive if there are less noodles
            than the number chosen, the philosopher eats all 
            remaining noodles
            - eating message
            - yield a random number of times, between 0 and 4
            inclusive, to simulate the time to eat the noodles
            - put down forks
            - if eaten all the noodles, stop looping
            - thinking message
            - yield a random number of times, between 0 and 19
            inclusive, to simulate the time to think
            - finish message
 return:
 ********************************************************/
void Philosopher::main(){
    unsigned int eating_noodles = 0;
    while(true){
        printer.print(this->id, Philosopher::Hungry);
        yield(mprng(4));//randomly yield 0 - 4
        this->table.pickup(this->id);// try to pick up forks
        eating_noodles = mprng(1,5);
        if(eating_noodles > this->noodles){
            eating_noodles = this->noodles; // prepare to eat all remained noodles
        }
        this->noodles -= eating_noodles;
        printer.print(this->id, Philosopher::Eating, eating_noodles, this->noodles);
        yield(mprng(4));
        this->table.putdown(this->id);// put down forks
        if(this->noodles < 1) break;
        printer.print(this->id, Philosopher::Thinking);// philosopher starts to think
        yield(mprng(19));
    }
    printer.print(this->id, Philosopher::Finished);//print finish message
}