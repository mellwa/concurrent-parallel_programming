#ifndef TRUCK_H
#define TRUCK_H

#include "bottling_plant.h"

_Task Truck{
public:
  Truck(Printer& prt,NameServer& nameServer,BottlingPlant& plant,unsigned int numVendingMachines,unsigned int maxStockPerFlavour);
    ~Truck();
private:
    Printer& prt;
    NameServer& nameServer;
    BottlingPlant& plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    unsigned int cargo[4];
    unsigned int total_cargo_num;
    void ThrowAwayPastCargo();
    int total_cargo();
    void main();
};

#endif

