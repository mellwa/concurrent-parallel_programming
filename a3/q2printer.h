#ifndef _Q2PRINTER_H   
#define _Q2PRINTER_H

#include "q2voter.h"
using namespace std;


_Monitor Printer {     // chose one of the two kinds of type constructor
private:
    unsigned int voters;
    unsigned int *numBlocked;//record the number of blocked tasks
    Voter::States *bufferSlots;//array of states for each voter
    bool *hasState;//record if the voter already has a state(used for flush)
    bool *votes;//the ballot
    void flushSlots();
    void voteFinished(unsigned int id, bool vote);
public:
    Printer( unsigned int voters );
    ~Printer();//destructor
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, bool vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif