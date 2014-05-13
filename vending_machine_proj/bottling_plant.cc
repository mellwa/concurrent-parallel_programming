/***
 This file contains the source code of BottlingPlant.
 
 It contains four functions: a constructor, a destructor, getShipments and action.
 
 1. BottlingPlant constructor will create a truck on heap, performing a production
 run, and distributing these bottles to initialize the registered vending machines
 using the truck. The BottlingPlant produces random new quantities of each flavour
 of soda, [0, MaxShippedPerFlavour], per flavour.
 2. ~BottlingPlant is a destructor, ending BottlingPlant, deleting truck on heap.
 3. getShipment obtains a shipment from the production run, and the shipment is
 copied into the cargo arry passed by the truck.
 4. action consumes nothing and produces nothing. There is a 1/5 chance the Bottling
 Plant is on strike. If on strike, the BP returns without continuing any work;
 otherwise, the bottling plant will check whether the truck has came back from the
 last delivery. There is 1/TimeBetwwenShipments chance that truck has return.
 If the truck has not came back, then BP will do nothing. If the truck has came
 back, it will perform a new producetion run and then truck will deliver bottles 
 to vending machines.
 
 ***/

#include "bottling_plant.h"
#include "truck.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;

/************ BottlingPlant::BottlingPlant **************************
 Purpose: Contructor. Initializing members
 
 Returns:
 *******************************************************************/
BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments), closingDown(false){
    
    prt.print(Printer::BottlingPlant,'S');
    this->truck = new Truck(prt,nameServer,*this,numVendingMachines,maxStockPerFlavour);
    for(int i = 0; i < 4; i++){
        this->flavour[i] = 0;
    }
}

/************ BottlingPlant::getShipment ****************************
 Purpose: Called truck such that truck can obtain a shipment from
          plant
 
 Returns: Boolean
 *******************************************************************/
bool BottlingPlant::getShipment(unsigned int cargo[]){
    if(closingDown){
        return true;
    }
    int total = 0;
    for(int i = 0; i < 4; i++){
        cargo[i] = flavour[i];
        total += cargo[i];
    }
    for(int j = 0; j < 4; j++){
        flavour[j] = 0;
    }
    return false;
}

/************ BottlingPlant::BottlingPlant **************************
 Purpose: The main function of bottling plant. It product soda and
          let truck deliver them to vending machines
 
 Returns:
 *******************************************************************/
void BottlingPlant::main(){
	for(;;) {
		yield(this->timeBetweenShipments);
		for (unsigned int i = 0; i < 4; ++i) {
			this->flavour[i] = mprng(0,this->maxStockPerFlavour);
		}
        int total = 0;
        for(int i = 0; i < 4; i++){
            total += flavour[i];
        }
		this->prt.print(Printer::BottlingPlant, 'G', total);
        _Accept(~BottlingPlant) {
			closingDown = true;
			_Accept(getShipment);
			break;
		}or _Accept(getShipment) {
			this->prt.print(Printer::BottlingPlant, 'P');
		}
	} // for
	this->prt.print(Printer::BottlingPlant, 'F');
    
    
}

/************ BottlingPlant::~BottlingPlant **************************
 Purpose: Free memory allocated on heap
 
 Returns: Nothing
 Errors: Nothing
 *******************************************************************/
BottlingPlant::~BottlingPlant(){
    delete this->truck;
}














