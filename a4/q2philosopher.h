#ifndef _Q2PHILOSOPHER_H_
#define _Q2PHILOSOPHER_H_

#include "q2table.h"
using namespace std;


_Task Philosopher {
private:
    unsigned int id;
    unsigned int noodles;
    Table &table;
    Printer &printer;
    void main();
public:
    enum States { Thinking = 'T', Hungry = 'H', Eating ='E',
        Waiting = 'W', Barging = 'B', Finished = 'F' };
    Philosopher( unsigned int id, unsigned int noodles, Table &table, Printer &prt );
};



#endif