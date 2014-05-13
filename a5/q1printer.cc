#include "q1printer.h"
#include <iostream>
using namespace std;

extern int numVoters;//global variable for number of voters

/*****************Printer::Printer***********************
 Purpose: constructor of Printer
           print out the first two lines
 
 return:
 ********************************************************/
Printer::Printer( unsigned int voters ) : voters(voters){
    //allocate variables
    this->bufferSlots = new Voter::States[voters];
    this->hasState = new bool[voters];
    this->votes = new bool[voters];
    this->numBlocked = new unsigned int[voters];
    for(int i = 0; i < voters-1; i++){
        this->hasState[i] = false;
        cout<<"Voter"<<i<<'\t';
    }
    this->hasState[voters-1] = false;
    cout<<"Voter"<<voters-1<<endl;
    for(int j = 0; j < voters-1; j++){
        cout<<"======="<<'\t';
    }
    cout<<"======="<<endl;

}

/*****************Printer::flushSlots*****************************
 Purpose: Since the voter overwrite his state, call the flushSlots
          to print out all other voters' states
 return:
 *****************************************************************/
void Printer::flushSlots(){
    int last_index = -1;//define the last index has a state
    for(int j = 0; j < this->voters;j++){
        if(this->hasState[j]){
            last_index = j;
        }
    }
    for(int i = 0; i <= last_index; i++){
        if(i != 0) cout<<'\t';
        if(this->hasState[i]){//if the voter has a state, print it out
            cout<<(char)this->bufferSlots[i];
            switch (this->bufferSlots[i]) {
                case Voter::Start:
                    break;
                case Voter::Vote:
                    cout<<" "<<this->votes[i];
                    break;
                case Voter::Block:
                    cout<<" "<<this->numBlocked[i];
                    break;
                case Voter::Unblock:
                    cout<<" "<<this->numBlocked[i];
                    break;
                case Voter::Complete:
                    break;
                default:
                    break;
            }
            this->hasState[i] = false;
        }
    }
    cout<<endl;
}

/*****************Printer::voteFinished***********************
 Purpose: flush since there is a vote has finished
 
 return:
 ********************************************************/
void Printer::voteFinished(unsigned int id, bool vote){
    for(int i = 0; i < this->voters; i++){
        if(i != id){
            cout<<"...";
        }
        else{
            cout<<"F "<<vote;
        }
        if(i < this->voters-1)
        cout<<'\t';
    }
    if(numVoters > 1)
    cout<<endl;
}

/*****************Printer::print***********************
 Purpose: print a voter's state
 
 return:
 ********************************************************/
void Printer::print( unsigned int id, Voter::States state ){
    if(this->hasState[id]){
        flushSlots();
    }
    this->bufferSlots[id] = state;//save the current state
    this->hasState[id] = true;
}

/*****************Printer::print***********************
 Purpose: print a voter's state with the his ballot
 
 return:
 ********************************************************/
void Printer::print( unsigned int id, Voter::States state, bool vote ){
    if(this->hasState[id]){
        flushSlots();
    }
    if(state != Voter::Finished){
        this->votes[id] = vote;
        this->bufferSlots[id] = state;
        this->hasState[id] = true;
    }
    else{
        this->voteFinished(id,vote);
    }
}

/*****************Printer::print***********************
 Purpose: print a voter's state with number of blocked tasks
 
 return:
 ********************************************************/
void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked ){
    if(this->hasState[id]){
        flushSlots();
    }
    this->numBlocked[id] = numBlocked;
    this->bufferSlots[id] = state;
    this->hasState[id] = true;
}

/*****************Printer::~Printer***********************
 Purpose: destructor
 
 return:
 ********************************************************/
Printer::~Printer(){
    this->flushSlots();
    cout<<"================="<<endl;//print out the last two lines
    cout<<"All tours started"<<endl;
    //deallocate all dynamic allocation variables
    delete[] this->bufferSlots;
    delete[] this->hasState;
    delete[] this->votes;
    delete[] this->numBlocked;
}

