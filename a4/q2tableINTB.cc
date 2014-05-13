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
    phil_is_eating = new bool[NoOfPhil];
    waiting_phils = 0;
    signaled_phils = 0;
    for(unsigned int j = 0; j < NoOfPhil; j++){
        this->phil_is_eating[j] = false;
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
          wait until he can pick two forks up
 
 return:
 ********************************************************/
void Table::pickup( unsigned int id ){
    unsigned int left_id = LeftPhil(id);
    unsigned int right_id = RightPhil(id);
    // since the number of signaled philosophers will be decrease
    // to zero, this looping will not cause busy waiting
    while(signaled_phils > 0){
        this->printer.print(id, Philosopher::Barging);
        wait();
        assert(this->signaled_phils >= 0);
    }
    
    // since the number of noodles is bounded by input number
    // this looping will not cause busy waiting
    while(phil_is_eating[left_id] || phil_is_eating[right_id]){
        this->printer.print(id, Philosopher::Waiting);
        this->waiting_phils++;
        wait();
        this->waiting_phils--;// number of waiting phils decreases
        this->signaled_phils--;// number of signaled phils decreases
        assert(this->waiting_phils >= 0);
        assert(this->signaled_phils >= 0);
    }
    assert(phil_is_eating[right_id] == false);
    assert(phil_is_eating[left_id] == false);
    assert(phil_is_eating[id] == false);
    phil_is_eating[id] = true;
}


/*****************Table::put down***********************
 Purpose: put down the two forks and set eating flag variable
          to false. Signal all blocked tasks on condition
          variable
 
 return:
 ********************************************************/
void Table::putdown( unsigned int id ){
    unsigned int right_id = RightPhil(id);
    unsigned int left_id = LeftPhil(id);
    assert(phil_is_eating[left_id] == false);
    assert(phil_is_eating[right_id] == false);
    assert(phil_is_eating[id] == true);
    phil_is_eating[id] = false;
    signalAll();
    this->signaled_phils = this->waiting_phils;
}


/*****************Table::~Table***********************
 Purpose: destructor
 
 return:
 ********************************************************/
Table::~Table(){
    delete[] phil_is_eating;
}


/*****************Table::wait***********************
 Purpose: barging and no forks philosopers will wait here
          also they will wake up here and there is some
          probability to allow barging task get into table
 
 return:
 ********************************************************/
void Table::wait() {
    noforks.wait();                         // wait until signalled
    while ( rand() % 5 == 0 ) {             // multiple bargers allowed
        _Accept( pickup, putdown ) {        // accept barging callers
        } _Else {                           // do not wait if no callers
        } // _Accept
    } // while
}

/*****************Table::signalALL***********************
 Purpose: signal all tasks waiting on condition variable
 
 return:
 ********************************************************/
void Table::signalAll() {                   // also useful
    while ( ! noforks.empty() ) noforks.signal(); // drain the condition
}

