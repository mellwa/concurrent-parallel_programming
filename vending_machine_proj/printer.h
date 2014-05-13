#ifndef PRINTER_H
#define PRINTER_H

using namespace std;

_Monitor Printer{
public:
  enum Kind{
    Parent,
    WATCardOffice,
    NameServer,
    Truck,
    BottlingPlant,
    Student,
    Vending,
    Courier
  };
  Printer(unsigned int numStudents,unsigned int numVendingMachines,unsigned int numCouriers);
  ~Printer();
  void print(Kind kind,char state);
  void print(Kind kind,char state,int value1);
  void print(Kind kind,char state,int value1,int value2);
  void print(Kind kind,unsigned int lid,char state);
  void print(Kind kind,unsigned int lid,char state,int value1);
  void print(Kind kind,unsigned int lid,char state,int value1,int value2);
private:
  int get_index(Kind kind);
  void print_line();
  unsigned int m_total;
  unsigned int m_numStudents;
  unsigned int m_numVendingMachines;
  unsigned int m_numCouriers;
  char* m_states;                 // Current states
  bool* m_valids;                 // If the states need to be printed
  bool* m_applys1;                // If there is first value attached
  bool* m_applys2;                // If there is second value attached
  unsigned int* m_values1;        // First value
  unsigned int* m_values2;        // Second value
};

#endif

