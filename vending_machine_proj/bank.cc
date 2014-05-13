/******************
Bank behaves like a server that manages student-account 
information for all students. Each student's account initially 
starts with a balance $0. The parent calls deposit to endow 
gifts to a specific student. A courier calls withdraw to transfer
money on behalf of the WATCard office for a specific student. 
The courier waits until enough money has been deposited, 
which may require multiple deposits.
******************/
#include "bank.h"

/*********** Bank::Bank ***************
Purpose: constructor to initialize 
         members
 
Returns:
**************************************/
Bank::Bank(unsigned int numStudents){
  m_values=new unsigned int[numStudents];
  for(int i=0;i<numStudents;i++){
    m_values[i]=0;
  }
}

/*********** Bank::~Bank ***************
 Purpose: destructor. delete student values
 
 Returns:
 **************************************/
Bank::~Bank(){
  delete[] m_values;
}

/*********** Bank::deposit **************
 Purpose: called by parent that randomly
          endow gifts to a specific student
 
 Returns:
 **************************************/
void Bank::deposit(unsigned int id,unsigned int amount){
  m_values[id]=m_values[id]+amount;
  m_withdraw.signal();
}

/*********** Bank::withdraw **************
 Purpose: Call by courier to transfer money
          on behalf of WATCard office for 
          a specific student.
 
 Returns:
 **************************************/
void Bank::withdraw(unsigned int id,unsigned int amount){
  while(m_values[id]<amount){
    m_withdraw.wait();
  }
  m_values[id]=m_values[id]-amount;
}

