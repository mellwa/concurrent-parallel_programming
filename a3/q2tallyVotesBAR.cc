#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <uBarrier.h>
#include <iostream>
using namespace std;

extern int numVoters;

/*****************TallyVotes::TallyVotes***********************
 Purpose: constructor.
 
 return:
 ********************************************************/
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : uBarrier(group), group(group), printer(printer), vote_members(0), blocked(0){
}


/*****************TallyVotes::vote***********************
 Purpose: synchronize all voters here and counting the
 result for each group. Printing out the state
 of each voter
 
 return: (boolean) final result
 ********************************************************/
bool TallyVotes::vote( unsigned int id, bool ballot ){
    bool result;

    //count the result
    if(this->vote_members == 0){
        this->outcome = (int)ballot;
    }
    else{
        if(ballot){
            this->outcome += 1;
        }
        else{
            this->outcome -= 1;
        }
    }
    assert(this->vote_members < this->group);
    this->vote_members ++;
    
    this->printer.print(id,Voter::Vote,ballot);
    if(vote_members<this->group){
        this->blocked++;
        this->printer.print(id,Voter::Block,this->blocked);
        this->block();//block the 1st - N-1th task and wait the Nth to unblock them
        this->blocked--;
        this->printer.print(id,Voter::Unblock,this->blocked);
    }
    else{
        this->block();
        this->printer.print(id,Voter::Complete);
    }
    this->vote_members--;//number of voter who has been voted decrease
    
    if(this->outcome > 0){
        result = true;
    }
    else{
        result = false;
    }
    this->printer.print(id,Voter::Finished,result);
    numVoters--;
    return result;
}

/*****************TallyVotes::TallyVotes***********************
 Purpose: destructor.
 
 return:
 ********************************************************/
TallyVotes::~TallyVotes(){
}