#include "q1tallyVotes.h"
#include "q1printer.h"
#include "q1voter.h"
#include <iostream>
using namespace std;

extern int numVoters;

/*****************TallyVotes::TallyVotes***********************
 Purpose: constructor. Using automatic-signal monitor
 
 return:
 **************************************************************/
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : blocked(0), group(group), printer(printer), vote_members(0){
    
}


/*****************TallyVotes::Block_task***********************
 Purpose: helper function, to do the task before blocked
 
 return:
 *************************************************************/
void TallyVotes::Block_task(unsigned int id){
    this->blocked++;
    this->printer.print(id,Voter::Block,this->blocked);
}


/*****************TallyVotes::Unblock_task*************************
 Purpose: helper function, to do the task after the task unblocked
 
 return:
 *****************************************************************/
void TallyVotes::Unblock_task(unsigned int id){
    this->blocked--;
    this->printer.print(id,Voter::Unblock,this->blocked);
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
    //wait until the condition is true
    WAITUNTIL((this->blocked >= this->group - 1),Block_task(id),Unblock_task(id));
    
    if(this->blocked == this->group - 1){
        this->printer.print(id,Voter::Complete);
    }
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
    RETURN(result);
}

/*****************TallyVotes::TallyVotes***********************
 Purpose: destructor.
 
 return:
 ********************************************************/
TallyVotes::~TallyVotes(){
    //deallocate locks
}