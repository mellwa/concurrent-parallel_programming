#include "q2voter.h"
#include "q2printer.h"
#include "MPRNG.h"
using namespace std;

extern MPRNG mprng;
extern int numVoters;

/*****************Voter::Voter***********************
 Purpose: constructor.
 
 return:
 ********************************************************/
Voter::Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer ) : id(id), voteTallier(voteTallier), printer(printer){}

/*****************Voter::main***********************
 Purpose: start a voter and the voter vote to voteTallier
 
 return:
 ********************************************************/
void Voter::main(){
    bool vote;
    bool result;
    this->printer.print(this->id, Voter::Start);
    
    yield(mprng(19));//randomly yield between 1-19
    vote = (bool)mprng(1);
    result = this->voteTallier.vote(this->id, vote);
}