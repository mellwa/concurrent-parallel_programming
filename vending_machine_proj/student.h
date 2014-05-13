#ifndef STUDENT_H
#define STUDENT_H

#include "printer.h"
#include "watcard_office.h"
#include "name_server.h"
#include "vending_machine.h"

_Task Student{
public:
  Student(Printer& prt,NameServer& nameServer,WATCardOffice& cardOffice,unsigned int id,unsigned int maxPurchases);
  ~Student();
private:
  void main();
  Printer& m_prt;
  NameServer& m_nameServer;
  WATCardOffice& m_cardOffice;
  WATCard::FWATCard m_future_card;
  WATCard* m_card;
  VendingMachine* m_machine;
  unsigned int m_id;
  unsigned int m_purchases;
  VendingMachine::Flavours m_flavour;
};

#endif

