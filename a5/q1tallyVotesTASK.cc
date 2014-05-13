#include "q1tallyVotes.h"
#include "q1printer.h"
#include "q1voter.h"
#include <iostream>
using namespace std;

extern int numVoters;

/*****************TallyVotes::TallyVotes***********************
 Purpose: constructor. using server task to perform maximum 
          amount of work on behalf of the client
 
 return:
 ********************************************************/
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : blocked(0), group(group), printer(printer), vote_members(0), pregroupdone(true){
    
}

/*****************TallyVotes::vote***********************
 Purpose: counting the result for each group. Printing out
          the state of each voter
 
 return: (boolean) final result
 ********************************************************/
bool TallyVotes::vote( unsigned int id, bool ballot ){
    bool result;
    this->tmp_taskid = id;
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
    this->printer.print(id,Voter::Vote,ballot);
    this->bench.wait();
    this->printer.print(id,Voter::Unblock,this->blocked);
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

/*****************TallyVotes::main***********************
 Purpose: a server task to synchronize voters
 
 return: (boolean) final result
 ********************************************************/
void TallyVotes::main(){
    while(true){
        _Accept(~TallyVotes){
            break;
        } or _Accept(vote){
            assert(this->vote_members < this->group);
            this->vote_members++;
            this->blocked++;
            this->printer.print(tmp_taskid,Voter::Block,this->blocked);
            if(this->blocked == this->group){
                this->printer.print(tmp_taskid,Voter::Complete);
                this->pregroupdone = false;
            }
            while(!this->pregroupdone){
                assert(this->blocked <= this->group);
                this->blocked--;
                assert(this->blocked >= 0);
                this->bench.signalBlock();
                this->vote_members--;
                if(this->blocked == 0){
                    this->pregroupdone = true;
                }
            }
        }
    }
}



/*****************TallyVotes::TallyVotes***********************
 Purpose: destructor.
 
 return:
 ********************************************************/
TallyVotes::~TallyVotes(){
    //deallocate locks
}