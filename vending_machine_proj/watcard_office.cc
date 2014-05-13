#include "watcard_office.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;
extern MPRNG mprng;

/************* WATCardOffice::Courier::Courier ************
 Purpose: constructor of Courier to initialize members
 
 Returns:
 **********************************************************/
WATCardOffice::Courier::Courier(Printer& prt,WATCardOffice& office,Bank& bank,unsigned int id):
  m_prt(prt),m_office(office),m_bank(bank),m_id(id){
}

/************* WATCardOffice::Courier::main ***************
 Purpose: 
 
 Returns:
 **********************************************************/
void WATCardOffice::Courier::main(){
  m_prt.print(Printer::Courier,m_id,'S');
  while(true){
    Job* job=m_office.requestWork();
    if(job==NULL){
      break;
    }
    m_prt.print(Printer::Courier,m_id,'t',job->m_id,job->m_amount);
    m_bank.withdraw(job->m_id,job->m_amount);
    m_prt.print(Printer::Courier,m_id,'T',job->m_id,job->m_amount);
    job->m_card->deposit(job->m_amount);
    if(!mprng(5)){
      job->m_result.exception(new Lost());
      delete job->m_card;
    }else{
      job->m_result.delivery(job->m_card);
      m_prt.print(Printer::WATCardOffice,'W');
    }
    delete job;
  }
  m_prt.print(Printer::Courier,m_id,'F');
}

/************* WATCardOffice::WATCardOffice ***************
 Purpose:
 
 Returns:
 **********************************************************/
WATCardOffice::WATCardOffice(Printer& prt,Bank& bank,unsigned int numCouriers):
  m_prt(prt),m_bank(bank),m_numCouriers(numCouriers),m_finished(false){
  m_couriers=new Courier*[m_numCouriers];
  for(int i=0;i<m_numCouriers;i++){
    m_couriers[i]=new Courier(m_prt,*this,m_bank,i);
  }
}

/************* WATCardOffice::~WATCardOffice **************
 Purpose:
 
 Returns:
 **********************************************************/
WATCardOffice::~WATCardOffice(){
  for(int i=0;i<m_numCouriers;i++){
    delete m_couriers[i];
  }
  delete[] m_couriers;
  while(!m_jobs.empty()){
    delete m_jobs.front();
    m_jobs.pop();
  }
}

/************* WATCardOffice::create **********************
 Purpose:
 
 Returns: WATCard::FWATCard
 **********************************************************/
WATCard::FWATCard WATCardOffice::create(unsigned int sid,unsigned int amount){
  Job* job=new Job(new WATCard(),sid,amount);
  m_jobs.push(job);
  m_request.signal();
  m_prt.print(Printer::WATCardOffice,'C',sid,amount);
  return job->m_result;
}

/************* WATCardOffice::transfer **********************
 Purpose:
 
 Returns: WATCard::FWATCard
 **********************************************************/
WATCard::FWATCard WATCardOffice::transfer(unsigned int sid,unsigned int amount,WATCard* card){
  Job* job=new Job(card,sid,amount);
  m_jobs.push(job);
  m_request.signal();
  m_prt.print(Printer::WATCardOffice,'T',sid,amount);
  return job->m_result;
}

/************* WATCardOffice::requestWork ******************
 Purpose:
 
 Returns: pointer of WATCardOffice::Job
 **********************************************************/
WATCardOffice::Job* WATCardOffice::requestWork(){
  if(!m_finished&&m_jobs.empty()){
    m_request.wait();
  }
  if(m_finished){
    m_request.signal();
    return NULL;
  }else{
    Job* job=m_jobs.front();
    m_jobs.pop();
    return job;
  }
}

/************* WATCardOffice::main ************************
 Purpose:
 
 Returns: 
 **********************************************************/
void WATCardOffice::main(){
  m_prt.print(Printer::WATCardOffice,'S');
  while(true){
    _Accept(~WATCardOffice){
      m_finished=true;
      m_request.signal();
      break;
    }or _Accept(create){
    }or _Accept(transfer){
    }or _Accept(requestWork){
    }
  }
  m_prt.print(Printer::WATCardOffice,'F');
}

