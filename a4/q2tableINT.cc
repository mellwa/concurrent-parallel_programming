#include "q2table.h"
#include "q2printer.h"
#include "q2philosopher.h"

#include <iostream>
using namespace std;

/*****************Table::Table***********************
 Purpose: constructor. Using Semaphore
 
 return:
 ********************************************************/
Table::Table( const unsigned int NoOfPhil, Printer &prt ) : printer(prt){
    this->NoOfPhil = NoOfPhil;
    this->forks = new uCondition[NoOfPhil];
    this->fork_is_occupied = new bool[NoOfPhil];
    //initialize state of each philosopher
    for(unsigned int j = 0; j < NoOfPhil; j++){
        this->fork_is_occupied[j] = false;
    }
}


/*****************Table::LeftPhil***********************
 Purpose: get the id of the left philosopher
 
 return: unsigned int
 ********************************************************/
unsigned int Table::LeftPhil(unsigned int id){
    int left_id = id;
    left_id -= 1;
    if(left_id < 0){
        left_id += this->NoOfPhil;
    }
    return (unsigned int)left_id;
}

/*****************Table::RightPhil***********************
 Purpose: get the id of the right philosopher
 
 return: unsigned int
 ********************************************************/
unsigned int Table::RightPhil(unsigned int id){
    int right_id = id;
    right_id = (id+1)%this->NoOfPhil;
    return (unsigned int)right_id;
}


/*****************Table::pickup***********************
 Purpose: pick up the forks on left and right. if any
          of them is unavailable, philosopher has to
          wait until he can pick two forks up. The even 
          ID fork has higher priority than odd ID fork
 
 
 return:
 ********************************************************/
void Table::pickup( unsigned int id ){
    unsigned int left_id = LeftPhil(id);
    unsigned int right_id = RightPhil(id);
    if(fork_is_occupied[id] || fork_is_occupied[right_id]){
        this->printer.print(id, Philosopher::Waiting);
        if(id%2 == 0){//if the id # is even, pick up the left fork first
            if(fork_is_occupied[id]){
                this->forks[id].wait();
            }
            assert(fork_is_occupied[id] == false);
            fork_is_occupied[id] = true;//set the fork to occupied
            
            if(fork_is_occupied[right_id]){
                this->forks[right_id].wait();
            }
            assert(fork_is_occupied[right_id]==false);
            fork_is_occupied[right_id] = true;
        }
        else{//if the id number is odd, pick up right fork first
            if(fork_is_occupied[right_id]){
                this->forks[right_id].wait();
            }
            assert(fork_is_occupied[right_id]==false);
            fork_is_occupied[right_id] = true;
            
            if(fork_is_occupied[id]){
                this->forks[id].wait();
            }
            assert(fork_is_occupied[id] == false);
            fork_is_occupied[id] = true;
        }
    }
    else{
        assert(fork_is_occupied[id] == false);
        assert(fork_is_occupied[right_id]==false);
        fork_is_occupied[id] = true;
        fork_is_occupied[right_id] = true;
    }
}

/*****************Table::put down***********************
 Purpose: put down the two forks and set flag variables
          to false. Also call the signal to wake up a task
          blocked on semaphores
 
 return:
 ********************************************************/
void Table::putdown( unsigned int id ){
    unsigned int right_id = RightPhil(id);
    if(!this->forks[id].empty()){
        this->forks[id].signal();
    }
    if(!this->forks[right_id].empty()){
        this->forks[right_id].signal();
    }
    assert(fork_is_occupied[id]==true);
    this->fork_is_occupied[id] = false;
    assert(fork_is_occupied[right_id]==true);
    this->fork_is_occupied[right_id] = false;
}

/*****************Table::~Table***********************
 Purpose: destructor
 
 return:
 ********************************************************/
Table::~Table(){
    delete[] this->forks;
    delete[] this->fork_is_occupied;
}
