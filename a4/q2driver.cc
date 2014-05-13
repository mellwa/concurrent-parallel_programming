#include "q2printer.h"
#include "q2table.h"
#include "q2philosopher.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

MPRNG mprng;

/*****************uMain::main***********************
 Purpose: run the main program. Getting argument and
          initializing variable. Handle the usage error
 
 return:
 ********************************************************/
void uMain::main(){
    int seed = getpid();
    int P = 5;
    int N = 30;
    //check the arguments
    switch (argc) {
        case 4:
            seed = atoi(argv[3]);
        case 3:
            N = atoi(argv[2]);
        case 2:
            P = atoi(argv[1]);
        case 1:
            break;
        default:
            cerr<<"Usage(too many arguments): "<<argv[0]<<"  [ philosophers (> 1) [ noodles (> 0) [ Seed (> 0) ] ] ]"<<endl;
            exit(1);
    }
    if(P < 2 || N < 1 || seed < 1){
        cerr<<"Error: "<<argv[0]<<"  [ philosophers (> 1) [ noodles (> 0) [ Seed (> 0) ] ] ]"<<endl;
        exit(1);
    }

    mprng.seed(seed);//initialize random number seed
    Printer printer(P);//define a printer for program
    Table table(P,printer);//create the table
    Philosopher* philosophers[P];
    
    for(int i = 0; i < P; i++){
        philosophers[i] = new Philosopher(i,N,table,printer);//define philosophers
    }
    
    for(int j = 0; j < P; j++){
        delete philosophers[j];//remove philosophers
    }
    uRetCode = 0;
}






