#include "watcard.h"

/******************* WATCard::WATCard ****************************
 Purpose: constructor build a watcard that stores id as uwid.
          Balance always start with zero.
 
 Returns:
 **********************************************************/
WATCard::WATCard():
  m_balance(0){
}

/******************* WATCard::deposite ****************************
 Purpose: called by courier after a funds transfer
 
 Returns:
 **********************************************************/
void WATCard::deposit(unsigned int amount){
  m_balance=m_balance+amount;
}

/******************* WATCard::withdraw ****************************
 Purpose: call this method since the a soda is purchased
 
 Returns:
 **********************************************************/
void WATCard::withdraw(unsigned int amount){
  m_balance=m_balance-amount;
}

/******************* WATCard::getBalance ****************************
 Purpose: called by student to determine the balance
 
 Returns:
 **********************************************************/
unsigned int WATCard::getBalance(){
  return m_balance;
}

