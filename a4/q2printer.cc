#include "q2printer.h"
#include <iostream>
using namespace std;

/*****************Printer::Printer***********************
 Purpose: constructor of Printer. Printing out the first
          two lines
 
 return:
 ********************************************************/
Printer::Printer( unsigned int NoOfPhil ) : NoOfPhil(NoOfPhil){
    this->hasState = new bool[NoOfPhil];
    this->bufferSlots = new Philosopher::States[NoOfPhil];
    this->bite = new unsigned int[NoOfPhil];
    this->noodles = new unsigned int[NoOfPhil];
    
    for(unsigned int i = 0; i < NoOfPhil-1; i++){
        this->hasState[i] = false;
        cout<<"Phil"<<i<<'\t';
    }
    this->hasState[NoOfPhil-1] = false;
    cout<<"Phil"<<NoOfPhil-1<<endl;
    for(unsigned int j = 0; j < NoOfPhil-1; j++){
        cout<<"******"<<'\t';
    }
    cout<<"******"<<endl;
}

/*****************Printer::flushSlots*****************************
 Purpose: flush the slot if there has already been a state
 
 return:
 *****************************************************************/
void Printer::flushSlots(){
    int last_index = -1;
    for(unsigned int j = 0; j < this->NoOfPhil;j++){
        if(this->hasState[j]){
            last_index = j;// get the last index has a state
        }
    }
    for(int i = 0; i <= last_index; i++){
        if(i != 0) cout<<'\t';
        if(this->hasState[i]){//if the voter has a state, print it out
            cout<<(char)this->bufferSlots[i];
            switch (this->bufferSlots[i]) {
                case Philosopher::Hungry:
                    break;
                case Philosopher::Thinking:
                    break;
                case Philosopher::Barging:
                    break;
                case Philosopher::Waiting:
                    cout<<i<<","<<(i+1)%this->NoOfPhil;
                    break;
                case Philosopher::Eating:
                    cout<<this->bite[i]<<","<<this->noodles[i];
                    break;
                default:
                    break;
            }
            this->hasState[i] = false;
        }
    }
    cout<<endl;
    
}

/*****************Printer::Finished***********************
 Purpose: flush since there is a philosopher has finished
 
 return:
 ********************************************************/
void Printer::Finished(unsigned int id){
    for(unsigned int i = 0; i < this->NoOfPhil; i++){
        if(i != id){
            cout<<"...";
        }
        else{
            cout<<"F";
        }
        if(i < this->NoOfPhil-1)
            cout<<'\t';
    }
    cout<<endl;
}

/*****************Printer::print***********************
 Purpose: print a Philosopher's state
 
 return:
 ********************************************************/
void Printer::print( unsigned int id, Philosopher::States state ){
    if(this->hasState[id]){
        flushSlots();//flush the slot
    }
    if(state != Philosopher::Finished){
        this->bufferSlots[id] = state;
        this->hasState[id] = true;
    }
    else{
        this->Finished(id);
    }
}


/*****************Printer::print***********************
 Purpose: print a Philosopher's state
 
 return:
 ********************************************************/
void Printer::print( unsigned int id, Philosopher::States state, unsigned int bite, unsigned int noodles ){
    if(this->hasState[id]){
        flushSlots();
    }
    this->bufferSlots[id] = state;
    this->hasState[id] = true; // set this slot has a state already
    this->bite[id] = bite; // set the number of noodles to be eaten
    this->noodles[id] = noodles; // set the remained number of noodles
}

/*****************Printer::~Printer***********************
 Purpose: destructor
 
 return:
 ********************************************************/
Printer::~Printer(){
    //this->flushSlots();
    cout<<"***********************"<<endl;//print out the last two lines
    cout<<"Philosophers terminated"<<endl;
    //deallocate all dynamic allocation variables
    delete[] this->hasState;
    delete[] this->bufferSlots;
    delete[] this->bite;
    delete[] this->noodles;
}










