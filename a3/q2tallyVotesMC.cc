#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <iostream>
using namespace std;

extern int numVoters;

/*****************TallyVotes::TallyVotes***********************
 Purpose: constructor. Using uOwnerLock and
 
 return:
 ********************************************************/
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : group(group), printer(printer), vote_members(0), barging(false){
    this->olk = new uOwnerLock();//allocate uOwner lock
    this->clk_blocking = new uCondLock();
    this->clk_barging = new uCondLock();
}

/*****************TallyVotes::vote***********************
 Purpose: synchronize all voters here and counting the 
          result for each group. Printing out the state
          of each voter
 
 return: (boolean) final result
 ********************************************************/
bool TallyVotes::vote( unsigned int id, bool ballot ){
    this->olk->acquire();//acquire mutex lock
    bool result;
    if(this->barging){
        this->clk_barging->wait(*this->olk);//block the barging task
    }
    if(this->vote_members == 0){
        this->outcome = (int)ballot;
    }
    else{
        if(ballot){//counting voting result
            this->outcome += 1;
        }
        else{
            this->outcome -= 1;
        }
    }
    assert(this->vote_members < this->group);
    this->vote_members ++;
    
    this->printer.print(id,Voter::Vote,ballot);//print the voter's ballot
    if(vote_members<this->group){
        this->blocked++;
        this->printer.print(id,Voter::Block,this->blocked);
        if(!this->clk_barging->empty()){
            this->clk_barging->signal();//wake up a task on baring lock
        }
        else{
            this->barging = false;
        }
        this->clk_blocking->wait(*this->olk);//blocking lock for blocked voter
        this->blocked--;
        this->printer.print(id,Voter::Unblock,this->blocked);
    }
    else{
        this->barging = true;
        this->printer.print(id,Voter::Complete);

    }
    
    if(!this->clk_blocking->empty()){
        this->clk_blocking->signal();//wake up a task on blocking lock
    }
    
    this->vote_members--;
    if(this->vote_members == 0){
        if(!this->clk_barging->empty()){
            this->clk_barging->signal();
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
    this->printer.print(id,Voter::Finished,result);//the voter finished
    numVoters--;
    this->olk->release();
    return result;
}

/*****************TallyVotes::TallyVotes***********************
 Purpose: destructor.
 
 return:
 ********************************************************/
TallyVotes::~TallyVotes(){
    //deallocate locks
    delete this->olk;
    delete this->clk_blocking;
    delete this->clk_barging;
}