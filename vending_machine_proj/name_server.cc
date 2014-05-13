/****************************************************
 This is a source file for NameServer.
******************************************************/

#include "name_server.h"

/*********** NameServer::NameServer **********
 Purpose: constructor create a nameserver with 
          initialization for all the fields.
 
 Returns:
 *********************************************/
NameServer::NameServer(Printer& prt,unsigned int numVendingMachines,unsigned int numStudents):
  m_prt(prt),m_numVendingMachines(numVendingMachines),m_numStudents(numStudents),m_register_index(0){
  m_machines=new VendingMachine*[m_numVendingMachines];
  m_student_locations=new unsigned int[m_numStudents];
  for(int i=0;i<m_numStudents;i++){
    m_student_locations[i]=i%m_numVendingMachines;
  }
}

/*********** NameServer::~NameServer **********
 Purpose: destructor, ending NameServer, deleting 
          VMs in array
 
 Returns:
 *********************************************/
NameServer::~NameServer(){
  delete[] m_machines;
  delete[] m_student_locations;
}

/*********** NameServer::VMregister **********
 Purpose: consumes a vending machine pointer. 
          It will adding the input into array 
          (all the registed vending machine).
 
 Returns:
 *********************************************/
void NameServer::VMregister(VendingMachine* vendingmachine){
  m_prt.print(Printer::NameServer,'R',m_register_index);
  m_machines[m_register_index]=vendingmachine;
  m_register_index=m_register_index+1;
}

/*********** NameServer::getMachine **********
 Purpose: consume an id, and returns a pointer 
          to vending machine. If the id is
          smaller than numRegister, it will get 
          the VM from the array using index.
 
 Returns:
 *********************************************/
VendingMachine* NameServer::getMachine(unsigned int id){
  int location=m_student_locations[id];
  m_prt.print(Printer::NameServer,'N',id,location);
  m_student_locations[id]=(m_student_locations[id]+1)%m_numVendingMachines;
  return m_machines[location];
}

/*********** NameServer::getMachineList **********
 Purpose: consumes nothing, but return the array 
          that stores all the vending machines
          that are registed.

 Returns:
 *************************************************/
VendingMachine** NameServer::getMachineList(){
  return m_machines;
}

/*********** NameServer::main ****************
 Purpose: main function since the nameserver
          start to serve client.
 
 Returns:
 *********************************************/
void NameServer::main(){
  m_prt.print(Printer::NameServer,'S');
  while(m_register_index<m_numVendingMachines){
    _Accept(VMregister)
  }
  while(true){
    _Accept(~NameServer){
      break;
    }or _Accept(getMachine){
    }or _Accept(getMachineList){
    }
  }
  m_prt.print(Printer::NameServer,'F');
}

