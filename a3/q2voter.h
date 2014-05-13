#ifndef _Q2VOTER_H_
#define _Q2VOTER_H_
#include "q2tallyVotes.h"
using namespace std;

_Monitor Printer;

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