#ifndef NAME_SERVER_H
#define NAME_SERVER_H

#include "printer.h"
#include "vending_machine.h"

_Task VendingMachine;

_Task NameServer{
public:
  NameServer(Printer& prt,unsigned int numVendingMachines,unsigned int numStudents);
  ~NameServer();
  void VMregister(VendingMachine* vendingmachine);
  VendingMachine* getMachine(unsigned int id);
  VendingMachine** getMachineList();
private:
  void main();
  Printer& m_prt;
  unsigned int m_numVendingMachines;
  unsigned int m_numStudents;
  VendingMachine** m_machines;
  unsigned int* m_student_locations;
  unsigned int m_register_index;
};

#endif

