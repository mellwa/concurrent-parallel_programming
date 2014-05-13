#include "parent.h"

extern MPRNG mprng;

/*********** Parent::Parent **********
Purpose: constructor of parent to 
         initialize members
 
Returns:
**************************************/
Parent::Parent(Printer& prt,Bank& bank,unsigned int numStudents,unsigned int parentalDelay):
  m_prt(prt),m_bank(bank),m_numStudents(numStudents),m_parentalDelay(parentalDelay){
}

/*********** Parent::~Parent *********
Purpose: destructor. do nothing here
 
Returns:
**************************************/
Parent::~Parent(){
}

/*********** Parent::main ************
Purpose: keeping endow gifts to students
          until the task is terminated
     
Returns:
**************************************/
void Parent::main(){
  m_prt.print(Printer::Parent,'S');
  while(true){
    _Accept(~Parent){
      break;
    }_Else{
      yield(m_parentalDelay);
      unsigned int id=mprng(m_numStudents-1);
      unsigned int amount=mprng(1,3);
      m_prt.print(Printer::Parent,'D',id,amount);
      m_bank.deposit(id,amount);
    }
  }
  m_prt.print(Printer::Parent,'F');
}

