#include "q1tallyVotes.h"
#include "q1printer.h"
#include "q1voter.h"
#include <iostream>
using namespace std;

extern int numVoters;

/*****************TallyVotes::TallyVotes***********************
 Purpose: constructor. Using internal scheduling with barging
          tasks
 
 return:
 ********************************************************/
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : blocked(0), group(group), printer(printer), vote_members(0), signalled_voters(0){
    
}

/*****************TallyVotes::vote***********************
 Purpose: synchronize all voters here and counting the
          result for each group. Printing out the state
          of each voter
 
 return: (boolean) final result
 ********************************************************/
bool TallyVotes::vote( unsigned int id, bool ballot ){
    bool result;
    
    while(this->signalled_voters>0){
        //barging
        bench.wait();
    }
    
    
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
    if(this->blocked < group - 1){
        this->blocked++;
        this->printer.print(id,Voter::Block,this->blocked);
        wait();//wait at condition variable bench
        this->blocked--;
        this->printer.print(id,Voter::Unblock,this->blocked);
    }
    else{
        this->printer.print(id,Voter::Complete);
    }
    this->signalled_voters = this->blocked;
    signalAll();//wake up all blocked tasks
    assert(this->blocked < group);
    this->vote_members--;
    
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
    //deallocate locks
}

/*****************TallyVotes::wait***********************
 Purpose: tasks wait on bench and they may cause some task
          barging into tallyvotes when they wake up
 
 return:
 ********************************************************/
void TallyVotes::wait() {
    bench.wait();                              // wait until signalled
    while ( rand() % 5 == 0 ) {                // multiple bargers allowed
        _Accept( vote ) {                      // accept barging callers
        } _Else {                              // do not wait if no callers
        } // _Accept
    } // while
}

/*****************TallyVotes::signalAll***********************
 Purpose: wake up all tasks blocked on conditional variable
          bench
 
 return:
 ********************************************************/
void TallyVotes::signalAll() {                 // also useful
    while ( ! bench.empty() ) bench.signal();  // drain the condition
}