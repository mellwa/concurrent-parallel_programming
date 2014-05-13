#ifndef WATCARD_OFFICE_H
#define WATCARD_OFFICE_H

#include <queue>
#include "watcard.h"
#include "bank.h"
#include "printer.h"

_Task WATCardOffice{
private:
  struct Job{
    WATCard* m_card;
    unsigned int m_id;
    unsigned int m_amount;
    WATCard::FWATCard m_result;
    Job(WATCard* card,unsigned int id,unsigned int amount):
      m_card(card),m_id(id),m_amount(amount){
    }
  };
  _Task Courier{
    public:
      Courier(Printer& prt,WATCardOffice& office,Bank& bank,unsigned int id);
    private:
      void main();
      Printer& m_prt;
      WATCardOffice& m_office;
      Bank& m_bank;
      unsigned int m_id;
  };
public:
  _Event Lost{
  };
  WATCardOffice(Printer& prt,Bank& bank,unsigned int numCouriers);
  ~WATCardOffice();
  WATCard::FWATCard create(unsigned int sid,unsigned int amount);
  WATCard::FWATCard transfer(unsigned int sid,unsigned int amount,WATCard* card);
  Job* requestWork();
private:
  void main();
  Printer& m_prt;
  Bank& m_bank;
  unsigned int m_numCouriers;
  Courier** m_couriers;
  uCondition m_request;
  queue<Job*> m_jobs;
  bool m_finished;
};

#endif

