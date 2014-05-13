#include "q2table.h"
#include "q2printer.h"
#include "q2philosopher.h"
#include <uSemaphore.h>
#include <iostream>
using namespace std;

/*****************Table::Table***********************
 Purpose: constructor. Using Semaphore
 
 return:
 ********************************************************/
Table::Table( const unsigned int NoOfPhil, Printer &prt ) : printer(prt){
    this->NoOfPhil = NoOfPhil;
    this->sem = new uSemaphore(1);
    this->sem_barging = new uSemaphore(0);
    this->sem_fork = new uSemaphore*[NoOfPhil];
    this->phil_is_eating = new bool[NoOfPhil];
    
    //initialize state of each philosopher
    for(unsigned int j = 0; j < NoOfPhil; j++){
        this->phil_is_eating[j] = false;
    }
    //initialize semaphores
    for(unsigned int i = 0; i < NoOfPhil; i++){
        this->sem_fork[i] = new uSemaphore(1);
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
          wait until he can pick two forks up.The even
          ID fork has higher priority than odd ID fork
 
 return:
 ********************************************************/
void Table::pickup( unsigned int id ){
    this->sem->P();
    unsigned int left_id = LeftPhil(id);
    unsigned int right_id = RightPhil(id);
    
    if(id%2 == 0){//if the id number is even, pick up left fork first
        if(!this->sem_fork[id]->TryP()){
            this->sem->V();
            this->sem_fork[id]->P();//wait at left fork
            this->sem->P();
        }
        if(!this->sem_fork[right_id]->TryP()){
            this->sem->V();
            this->sem_fork[right_id]->P();//wait at right fork
            this->sem->P();
        }
    }
    else{//if the id number is odd, pick up right fork first
        if(!this->sem_fork[right_id]->TryP()){
            this->sem->V();
            this->sem_fork[right_id]->P();
            this->sem->P();
        }
        if(!this->sem_fork[id]->TryP()){
            this->sem->V();
            this->sem_fork[id]->P();
            this->sem->P();
        }
    }
    assert(phil_is_eating[right_id] == false);
    assert(phil_is_eating[left_id] == false);
    assert(phil_is_eating[id] == false);
    phil_is_eating[id] = true;
    this->sem->V();
}

/*****************Table::put down***********************
 Purpose: put down the two forks and set eating flag variable
          to false
 
 return:
 ********************************************************/
void Table::putdown( unsigned int id ){
    this->sem->P();
    unsigned int right_id = RightPhil(id);
    unsigned int left_id = LeftPhil(id);
    //make sure adjacent philosophers are not eating(barging)
    assert(phil_is_eating[right_id] == false);
    assert(phil_is_eating[left_id] == false);
    assert(phil_is_eating[id] == true);
    phil_is_eating[id] = false;
    this->sem_fork[id]->V();//wake up phil waiting at left fork
    this->sem_fork[right_id]->V();//wake up phil waiting at right fork
    this->sem->V();
}

/*****************Table::~Table***********************
 Purpose: destructor
 
 return:
 ********************************************************/
Table::~Table(){
    //delete all allocated variables
    delete this->sem;
    delete this->sem_barging;
    delete this->phil_is_eating;
    for(unsigned int i = 0; i < this->NoOfPhil; i++){
        delete this->sem_fork[i];
    }
    delete[] this->sem_fork;
}



