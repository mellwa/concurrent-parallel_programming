/***
 This file contains the source code of Truck.
 
 It constains three functions: a constructor, a destructor and action.
 
 1. Truck constructor will build a truck with with initialization for all the
 fields. Also, it will print out state "S" via printer. It will initialize
 cargo for all four flavour as zero and total_cargo as zero.
 2. ~Truck is a destructor, ending Truck, and printing "F" state to printer.
 3. Before delivering bottles, truck will check if the total_cargo is zero.
 If yes, it will do nothing; otherwise, it will distribute bottles for
 registered vending machines (every flavour). Once the bottles could not fill
 up a vending machine, truck will print "U" via printer, and go back to
 BottlingPlant.
 
 ***/

#include <iostream>
#include "truck.h"
#include "name_server.h"
#include "bottling_plant.h"
#include "vending_machine.h"
using namespace std;

extern MPRNG mprng;

/******************* Truck::Truck ****************************
 Purpose: Truck constructor will build a truck with with 
          initialization for all the fields. Also, it will 
          print out state "S" via printer.It will initialize
          cargo for all four flavour as zero and total_cargo
          as zero.
 
 Returns:
 **********************************************************/
Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,unsigned int numVendingMachines,
             unsigned int maxStockPerFlavour ) : prt(prt), nameServer(nameServer), plant(plant),
numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour){
    // initializing everything
    prt.print(Printer::Truck,'S');
    for(int i = 0; i < 4; i++){
        cargo[i] = 0;
    }
    total_cargo_num = 0;
}

/******************* Truck::ThrowAwayPastCargo **************
 Purpose: throw the cargo that are past due date
 
 Returns:
 **********************************************************/
void Truck::ThrowAwayPastCargo(){
    for(int i = 0; i < 4; i++){
        cargo[i] = 0;
    }
    this->total_cargo_num = 0;
}

/******************* Truck::total_cargo ****************************
 Purpose: calculate the total number of cargo in truck
 
 Returns:
 **********************************************************/
int Truck::total_cargo(){
    int total_cargo = 0;
    for(int i = 0; i < 4; i++){
        total_cargo += this->cargo[i];//calculate the total cargo number
    }
    return total_cargo;
}

/******************* Truck::main ****************************
 Purpose: main method to check if the total_cargo is zero. If yes, it will do nothing;
          otherwise, it will distribute bottles for registered vending machines 
          (every flavour). Once the bottles could not fill up a vending machine, 
          truck will print "U" via printer, and go back to BottlingPlant.
 
 Returns:
 **********************************************************/
void Truck::main(){
    VendingMachine** vendingMachines = this->nameServer.getMachineList();
    int total_needed = 0;
    int need=0;
    while(true){
        this->ThrowAwayPastCargo();
        yield(mprng(1,10));
        if(this->plant.getShipment(this->cargo)){
            break;
        }
        this->total_cargo_num = total_cargo();
        this->prt.print(Printer::Truck, 'P',this->total_cargo_num);
        for(unsigned int j = 0; j < this->numVendingMachines; j++){
            
            this->total_cargo_num = total_cargo();
            if(this->total_cargo_num == 0){
                break;
            }
            //vending machine j and remained cargo number total_cargo_num
            prt.print(Printer::Truck, 'd', j,total_cargo_num);
            unsigned int * flavours = vendingMachines[j]->inventory();
            total_needed = 4*this->maxStockPerFlavour - flavours[0]- flavours[1]- flavours[2]- flavours[3];
			for (int z = 0; z < 4; z++) {
                need = this->maxStockPerFlavour - flavours[z];
                int fill = need < this->cargo[z] ? need : this->cargo[z];
				flavours[z] += fill;
				this->cargo[z] -= fill;
				assert(this->cargo[z] >= 0);
                total_needed -= fill;
                if(this->total_cargo() == 0) break;//truck get empty
			}
            if(this->total_cargo() != 0){
                prt.print(Printer::Truck,'U',vendingMachines[j]->getId(),total_needed);
            }
			vendingMachines[j]->restocked();
            prt.print(Printer::Truck,'D',vendingMachines[j]->getId(),total_cargo());
        }
    }
}

/*******************Truck::~Truck****************************
 Purpose: destructor to print finish message
 
 Returns:
 **********************************************************/
Truck::~Truck(){
    this->prt.print(Printer::Truck, 'F');
}










