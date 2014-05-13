#include <uC++.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "config.h"
#include "student.h"
#include "printer.h"
#include "bank.h"
#include "watcard_office.h"
#include "vending_machine.h"
#include "parent.h"
#include "name_server.h"
#include "bottling_plant.h"

using namespace std;


MPRNG mprng;

/********************** usage *************************
 Purpose: output usage message
 
 Returns:
 ************************************************************/
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]" << endl;
    exit( EXIT_FAILURE );
} // usage

/********************** uMain::main *************************
 Purpose: the uMain function for program. It parses the command 
          line input, process config file, handles invalid input,
          and creates required tasks;
 
 Returns:  
 ************************************************************/
void uMain::main(){
    string configFile = "config.txt";
    int seed = getpid();
    // reading arguments from argument to program
    switch (argc) {
        case 3:
            seed = (int)atol(argv[2]);
        case 2:
        	configFile = argv[1];
        case 1:
            break;
        default:
            usage(argv);
            break;
    } // switch
    if (seed <= 0) {
        usage(argv);
    } // if
    ConfigParms pm;
    // set a random seed to generator
    mprng.seed(seed);
    processConfigFile(configFile.c_str(), pm);
    
    //declare printer for program
    Printer prt(pm.numStudents,pm.numVendingMachines, pm.numCouriers);
    Bank bank(pm.numStudents);//declare bank
    WATCardOffice office(prt, bank, pm.numCouriers);
    
    Parent parent(prt, bank, pm.numStudents, pm.parentalDelay);
    
    NameServer nameServer(prt, pm.numVendingMachines, pm.numStudents);
    VendingMachine *vms[pm.numVendingMachines];
    for (unsigned int i = 0; i < pm.numVendingMachines; ++i) {
        vms[i] = new VendingMachine(prt, nameServer, i, pm.sodaCost, pm.maxStockPerFlavour);
    }
    BottlingPlant *plant = new BottlingPlant(prt, nameServer, pm.numVendingMachines, pm.maxShippedPerFlavour,
                                             pm.maxStockPerFlavour, pm.timeBetweenShipments);
    Student * students[pm.numStudents];
    for (unsigned int i = 0; i < pm.numStudents; i++) {
        students[i] = new Student(prt, nameServer, office, i, pm.maxPurchases);
    }
    for (unsigned int j = 0; j < pm.numStudents; j++) {
        delete students[j];//student j done his work
    }
    
    delete plant;
    for (unsigned int k = 0; k < pm.numVendingMachines; k++) {
        delete vms[k];//vending machine id: k done its work
    }
    
}
