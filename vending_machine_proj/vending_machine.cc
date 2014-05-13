/****************************************************
 This is a source file for VendingMachine. (VM refers to VendingMachine)
 2. ~VM is a destructor, ending VM.
 3. buy will be implemented in the two derived classes.
 4. inventory() will consume nothing and return its own soda_flavour stock.
 5. restocked() will consume nothing but will be called by Truck to indicating delivery
 completed.
 6. cost() will consume nothing and return its own flavour_cost, which is the
 regular soda cost.
 7. getId() will consume nothing and return its own idnum that associated with this VM.
 ***/
 
#include "vending_machine.h"

/******************* VendingMachine::VendingMachine **************
 Purpose: constructor. create a regular VM with initialization for all the fields.
 
 Returns:
 ****************************************************************/
VendingMachine::VendingMachine(Printer& prt,NameServer& nameServer,unsigned int id,unsigned int sodaCost,
                               unsigned int maxStockPerFlavour):
  m_prt(prt),m_nameServer(nameServer),m_id(id),m_sodaCost(sodaCost),m_maxStockPerFlavour(maxStockPerFlavour),
  m_restocking(false){
  m_nameServer.VMregister(this);
  for(int i=0;i<4;i++){
    m_soda_flavour[i]=0;
  }
}

/******************* VendingMachine::buy **************
 Purpose: called by student to give the student his favourite sodas
 
 Returns: VendingMachine::Status
 ****************************************************************/
VendingMachine::Status VendingMachine::buy(Flavours flavour,WATCard& card){
  if(m_restocking){
    _Accept(restocked);
  }
  if(m_soda_flavour[flavour]<=0){
    return STOCK;
  }else if(card.getBalance()<m_sodaCost){
    return FUNDS;
  }
  card.withdraw(m_sodaCost);
  m_soda_flavour[flavour]=m_soda_flavour[flavour]-1;
  m_prt.print(Printer::Vending,m_id,'B',flavour,m_soda_flavour[flavour]);
  return BUY;
}

/******************* VendingMachine::invetory **************
 Purpose: return the remained soda info
 
 Returns: pointer of integer
 ****************************************************************/
unsigned int* VendingMachine::inventory(){
  m_restocking=true;
  return m_soda_flavour;
}

/******************* VendingMachine::restocked **************
 Purpose: called by truck to indicate the operation is complete
 
 Returns:
 ****************************************************************/
void VendingMachine::restocked(){
  m_restocking=false;
}

/******************* VendingMachine::cost **************
 Purpose: return the cost of purchasing soda
 
 Returns: _Nomutex
 ****************************************************************/
_Nomutex unsigned int VendingMachine::cost(){
  return m_sodaCost;
}

/******************* VendingMachine::getId **************
 Purpose: get the id of this vending machine
 
 Returns: _Nomutex
 ****************************************************************/
_Nomutex unsigned int VendingMachine::getId(){
  return m_id;
}

/******************* VendingMachine::main **************
 Purpose: 	1. print out start message
            2. register current vending machine to name server
            3. loop to wait client
            4. print out finished message
 
 Returns:
 ****************************************************************/
void VendingMachine::main(){
  m_prt.print(Printer::Vending,m_id,'S',m_sodaCost);
  while(true){
    _Accept(~VendingMachine){
      break;
    }or _Accept(buy){
    }or _Accept(inventory){
      m_prt.print(Printer::Vending,m_id,'r');
      _Accept(restocked){
        m_prt.print(Printer::Vending,m_id,'R');
      }
    }
  }
  m_prt.print(Printer::Vending,m_id,'F');
}

