#include "student.h"
#include "MPRNG.h"
extern MPRNG mprng;

/*********** Student::Student *************
 Purpose: constructor. Create a student 
         with initialization for all the fields.
 
 Returns:
 ******************************************/
Student::Student(Printer& prt,NameServer& nameServer,WATCardOffice& cardOffice,unsigned int id,
                 unsigned int maxPurchases):
  m_prt(prt),m_nameServer(nameServer),m_cardOffice(cardOffice),m_id(id){
  m_future_card=m_cardOffice.create(this->m_id,5);
  m_machine=m_nameServer.getMachine(m_id);
  m_purchases=mprng(1,maxPurchases);
  m_flavour=static_cast<VendingMachine::Flavours>(mprng(3));
}

/*********** Student::~Student **********
 Purpose: destructor, ending Student, 
          deleting WATCard on heap

 
 Returns:
 **************************************/
Student::~Student(){
  delete m_card;
}

/*********** Student::main **********************
 Purpose:1. select a random number of bottles to purchase [1, MaxPurchases]
         2. select a random favourite flavour [0, 3]
         3. start message
         4. create a WATCard via the WATCardOffice with a $5 balance
         5. obtain the location of a vending machine from the name server.
 
 Returns:
 **************************************************/
void Student::main(){
  m_prt.print(Printer::Student,m_id,'S',m_flavour,m_purchases);
  m_prt.print(Printer::Student,m_id,'V',m_machine->getId());
  for(int i=0;i<m_purchases;i++){
    new_machine:
    //yield a random number of times in the range [1, 10].
    yield(mprng(1,10));
    get_card:
    try{
      m_card=m_future_card();
    }catch(WATCardOffice::Lost event){
      m_prt.print(Printer::Student,m_id,'L');
      m_future_card=m_cardOffice.create(this->m_id,5);
      goto get_card;
    }
    VendingMachine::Status status=m_machine->buy(m_flavour,*m_card);
    if(status==VendingMachine::BUY){
      m_prt.print(Printer::Student,m_id,'B',m_card->getBalance());
    }else if(status==VendingMachine::STOCK){
      m_machine=m_nameServer.getMachine(m_id);
      m_prt.print(Printer::Student,m_id,'V',m_machine->getId());
      goto new_machine;
    }else if(status==VendingMachine::FUNDS){
      m_future_card=m_cardOffice.transfer(m_id,m_machine->cost()+5,m_card);
      goto get_card;
    }else{
    }
  }
  m_prt.print(Printer::Student,m_id,'F');//finished message
}

