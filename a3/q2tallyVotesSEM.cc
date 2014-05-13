#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <uSemaphore.h>
#include <iostream>
using namespace std;

extern int numVoters;

/*****************TallyVotes::TallyVotes***********************
 Purpose: constructor. Using Semaphore
 
 return:
 ********************************************************/
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : group(group), printer(printer), vote_members(0), barging(false){
    this->sem = new uSemaphore();
    this->sem_barging = new uSemaphore(0);
    this->sem_group = new uSemaphore(0);
}

/*****************TallyVotes::vote***********************
 Purpose: synchronize all voters here and counting the
          result for each group. Printing out the state
          of each voter.
          Similar with the uOwnerLock and uCondLock method
 
 return: (boolean) final result
 ********************************************************/
bool TallyVotes::vote( unsigned int id, bool ballot ){
    this->sem->P();//simulate uOwnerLock to provide mutual exclusion
    bool result;
    if(this->barging){
        this->sem->V();
        this->sem_barging->P();//baring tasks blocked here
        this->sem->P();
    }
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
        if(!this->sem_barging->empty()){
            this->sem_barging->V();
        }
        else{
            this->barging = false;
        }
        
        this->sem->V();
        this->sem_group->P();
        this->sem->P();
        this->blocked--;
        this->printer.print(id,Voter::Unblock,this->blocked);
    }
    else{
        this->barging = true;
        this->printer.print(id,Voter::Complete);
    }
    
    if(!this->sem_group->empty()){
        this->sem_group->V();
    }
    
    this->vote_members--;
    if(this->vote_members == 0){
        if(!this->sem_barging->empty()){
            this->sem_barging->V();
        }
        else{
            this->barging = false;
        }
    }
    
    if(this->outcome > 0){
        result = true;
    }
    else{
        result = false;
    }
    this->printer.print(id,Voter::Finished,result);
    numVoters--;
    this->sem->V();
    return result;
}

/*****************TallyVotes::TallyVotes***********************
 Purpose: destructor.
 
 return:
 ********************************************************/
TallyVotes::~TallyVotes(){
    delete this->sem;
    delete this->sem_group;
    delete this->sem_barging;
}