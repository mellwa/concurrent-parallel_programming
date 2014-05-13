#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
 
#include "printer.h"
#include "name_server.h"
#include "watcard.h"

_Task NameServer;
 
_Task VendingMachine{
public:
  enum Flavours{
    BLACK_CHERRY,
    CREAM_SODA,
    ROOT_BEER,
    LIME
  };
  enum Status{
    BUY,
    STOCK,
    FUNDS
  };
  VendingMachine(Printer& prt,NameServer& nameServer,unsigned int id,unsigned int sodaCost,unsigned int maxStockPerFlavour);
  Status buy(Flavours flavour,WATCard& card);
  unsigned int* inventory();
  void restocked();
  _Nomutex unsigned int cost();
  _Nomutex unsigned int getId();
private:
  void main();
  Printer& m_prt;
  NameServer& m_nameServer;
  unsigned int m_id;
  unsigned int m_sodaCost;
  unsigned int m_maxStockPerFlavour;
  unsigned int m_soda_flavour[4];
  bool m_restocking;
};
 
#endif

