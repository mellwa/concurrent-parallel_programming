#ifndef _Q1VOTER_H_
#define _Q1VOTER_H_

#include "q1tallyVotes.h"
using namespace std;

_Monitor Printer;//pre define printer

_Task Voter {
private:
    unsigned int id;
    TallyVotes &voteTallier;//the reference of voteTallier
    Printer &printer;//reference of printer
    void main();
public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
        Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer );
};

#endif
