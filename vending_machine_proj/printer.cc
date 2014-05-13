#include <iostream>
#include "printer.h"
using namespace std;

/*********** Printer::Printer ******************
Purpose: Constructor
Returns:
**************************************/
Printer::Printer(unsigned int numStudents,unsigned int numVendingMachines,unsigned int numCouriers):
  m_numStudents(numStudents),m_numVendingMachines(numVendingMachines),m_numCouriers(numCouriers){
  m_total=m_numStudents+m_numVendingMachines+m_numCouriers+5;
  m_states=new char[m_total];
  m_valids=new bool[m_total];
  m_applys1=new bool[m_total];
  m_applys2=new bool[m_total];
  m_values1=new unsigned int[m_total];
  m_values2=new unsigned int[m_total];
  for(int i=0;i<m_total;i++){
    m_valids[i]=false;
    m_applys1[i]=false;
    m_applys2[i]=false;
  }
  cout<<"Parent\tWATOff\tNames\tTruck\tPlant\t";
  for(int i=0;i<m_numStudents;i++){
    cout<<"Stud"<<i<<"\t";
  }
  for(int i=0;i<m_numVendingMachines;i++){
    cout<<"Mach"<<i<<"\t";
  }
  for(int i=0;i<m_numCouriers;i++){
    cout<<"Cour"<<i<<"\t";
  }
  cout<<endl;
  for(int i=0;i<m_total;i++){
    cout<<"*******\t";
  }
  cout<<endl;
}

/*********** Printer::~Printer *****************
Purpose: Destructor
Returns:
**************************************/
Printer::~Printer(){
  print_line();
  cout<<"***********************"<<endl;
  delete[] m_states;
  delete[] m_valids;
  delete[] m_applys1;
  delete[] m_applys2;
  delete[] m_values1;
  delete[] m_values2;
}

/*********** Printer::print **********
 Purpose: printer the given parameters
 to buffer
 
 Returns:
 **************************************/
void Printer::print(Kind kind,char state){
  int index=get_index(kind);
  if(m_valids[index]||state=='F'){
    print_line();
  }
  m_states[index]=state;
  m_valids[index]=true;
  if(state=='F'){
    for(int i=0;i<m_total;i++){
      if(i==index){
        continue;
      }
      m_states[i]='_';
      m_valids[i]=true;
    }
  }
}

/*********** Printer::print **********
 Purpose: printer the given parameters
 to buffer
 
 Returns:
 **************************************/
void Printer::print(Kind kind,char state,int value1){
  int index=get_index(kind);
  if(m_valids[index]){
    print_line();
  }
  m_states[index]=state;
  m_valids[index]=true;
  m_applys1[index]=true;
  m_values1[index]=value1;
}

/*********** Printer::print **********
 Purpose: printer the given parameters
 to buffer
 
 Returns:
 **************************************/
void Printer::print(Kind kind,char state,int value1,int value2){
  int index=get_index(kind);
  if(m_valids[index]){
    print_line();
  }
  m_states[index]=state;
  m_valids[index]=true;
  m_applys1[index]=true;
  m_applys2[index]=true;
  m_values1[index]=value1;
  m_values2[index]=value2;
}

/*********** Printer::print **********
 Purpose: printer the given parameters
 to buffer
 
 Returns:
 **************************************/
void Printer::print(Kind kind,unsigned int lid,char state){
  int index=get_index(kind)+lid;
  if(m_valids[index]||state=='F'){
    print_line();
  }
  m_states[index]=state;
  m_valids[index]=true;
  if(state=='F'){
    for(int i=0;i<m_total;i++){
      if(i==index){
        continue;
      }
      m_states[i]='_';
      m_valids[i]=true;
    }
  }
}

/*********** Printer::print **********
Purpose: printer the given parameters
         to buffer
 
Returns:
**************************************/
void Printer::print(Kind kind,unsigned int lid,char state,int value1){
  int index=get_index(kind)+lid;
  if(m_valids[index]){
    print_line();
  }
  m_states[index]=state;
  m_valids[index]=true;
  m_applys1[index]=true;
  m_values1[index]=value1;
}

/*********** Printer::print **********
 Purpose: printer the given parameters
 to buffer
 
 Returns:
 **************************************/
void Printer::print(Kind kind,unsigned int lid,char state,int value1,int value2){
  int index=get_index(kind)+lid;
  if(m_valids[index]){
    print_line();
  }
  m_states[index]=state;
  m_valids[index]=true;
  m_applys1[index]=true;
  m_applys2[index]=true;
  m_values1[index]=value1;
  m_values2[index]=value2;
}

/*********** Printer::get_index *********
Purpose: Get index of the kind
 
Returns: Index
*****************************************/
int Printer::get_index(Kind kind){
  if(kind==Parent){
    return 0;
  }else if(kind==WATCardOffice){
    return 1;
  }else if(kind==NameServer){
    return 2;
  }else if(kind==Truck){
    return 3;
  }else if(kind==BottlingPlant){
    return 4;
  }else if(kind==Student){
    return 5;
  }else if(kind==Vending){
    return 5+m_numStudents;
  }else if(kind==Courier){
    return 5+m_numStudents+m_numVendingMachines;
  }else{
    return -1;
  }
}

/*********** Printer::print_line ***************
Purpose: Print out a line, and flush the buffer
 
Returns:
**************************************/
void Printer::print_line(){
  for(unsigned int i=0;i<m_total;i++){
    if(m_valids[i]){
      if(m_states[i]=='_'){
        cout<<"...";
      }else{
        cout<<m_states[i];
      }
      m_valids[i]=false;
      if(m_applys1[i]){
        cout<<m_values1[i];
        m_applys1[i]=false;
        if(m_applys2[i]){
          cout<<','<<m_values2[i];
          m_applys2[i]=false;
        }
      }
    }
    cout<<"\t";
  }
  cout<<endl;
}

