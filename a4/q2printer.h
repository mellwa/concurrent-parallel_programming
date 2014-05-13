#ifndef _Q2PRINTER_H_
#define _Q2PRINTER_H_

#include "q2philosopher.h"
using namespace std;

_Monitor Printer {            // choose one of the two kinds of type constructor
private:
    unsigned int NoOfPhil;
    Philosopher::States *bufferSlots;//array of states for each philosopher
    bool *hasState;
    unsigned int *bite;
    unsigned int *noodles;
    void flushSlots();
    void Finished(unsigned int id);
public:
    Printer( unsigned int NoOfPhil );
    ~Printer();
    void print( unsigned int id, Philosopher::States state );
    void print( unsigned int id, Philosopher::States state, unsigned int bite, unsigned int noodles );
};


#endif