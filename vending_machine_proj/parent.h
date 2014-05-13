#ifndef PARENT_H
#define PARENT_H

#include "bank.h"
#include "printer.h"
#include "MPRNG.h"

_Task Parent{
public:
  Parent(Printer& prt,Bank& bank,unsigned int numStudents,unsigned int parentalDelay);
  ~Parent();
private:
  void main();
  Printer& m_prt;
  Bank& m_bank;
  unsigned int m_numStudents;
  unsigned int m_parentalDelay;
};

#endif

