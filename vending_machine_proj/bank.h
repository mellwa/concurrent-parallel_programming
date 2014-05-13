#ifndef BANK_H
#define BANK_H

using namespace std;

_Monitor Bank{
public:
  Bank(unsigned int numStudents);
  ~Bank();
  void deposit(unsigned int id,unsigned int amount);
  void withdraw(unsigned int id,unsigned int amount);
private:
  uCondition m_withdraw;
  unsigned int* m_values;
};

#endif

