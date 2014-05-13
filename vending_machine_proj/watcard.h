#ifndef WATCARD_H
#define WATCARD_H

#include <uFuture.h>

class WATCard{
public:
  WATCard();
  typedef Future_ISM<WATCard*> FWATCard;
  void deposit(unsigned int amount);
  void withdraw(unsigned int amount);
  unsigned int getBalance();
private:
  WATCard(const WATCard& target);
  WATCard& operator=(const WATCard& target);
  unsigned int m_balance;
};

#endif

