#ifndef BOTTLING_PLANT_H
#define BOTTLING_PLANT_H

#include "printer.h"
#include "name_server.h"
#include "MPRNG.h"

_Task Truck;

_Task BottlingPlant{
public:
  BottlingPlant(Printer& prt,NameServer& nameServer,
    unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour,
    unsigned int maxStockPerFlavour,
    unsigned int timeBetweenShipments);
  bool getShipment(unsigned int cargo[]);
    ~BottlingPlant();
private:
    Truck* truck;
    Printer& prt;
    NameServer& nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int flavour[4];
    bool closingDown;
    void main();
};

#endif

