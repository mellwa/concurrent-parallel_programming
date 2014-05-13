#include "q2printer.h"
#include "q2voter.h"
#include "q2tallyVotes.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

MPRNG mprng;//declare the pseudo random number variable
int numVoters;

/*****************uMain::main***********************
 Purpose: run the voting program. Getting argument and
          initializing variable. Handle the usage error
 
 return:
 ********************************************************/
void uMain::main(){
    int seed = getpid();
    int G = 3;
    int V = 6;
    //check the arguments
    switch (argc) {
        case 4:
            seed = atoi(argv[3]);
        case 3:
            G = atoi(argv[2]);
        case 2:
            V = atoi(argv[1]);
        case 1:
            break;
        default:
            cerr<<"Usage: "<<argv[0]<<"  Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)"<<endl;
            uRetCode = 0;
            return;
    }
    if(V<=0 || G<=0 || seed<=0){
        cerr<<"Usage: "<<argv[0]<<" Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)"<<endl;
        uRetCode = 0;
        return;
    }
    if(V%G != 0 || G%2 != 1 || V < G){
        cerr<<"Usage: "<<argv[0]<<"  Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)"<<endl;
        uRetCode = 0;
        return;
    }
    //initialize variables
    numVoters = V;
    mprng.seed(seed);
    Printer printer(V);
    Voter* voters[V];
    TallyVotes voteTallier(G,printer);
    
    for(int i = 0; i < V; i++){
        voters[i] = new Voter(i,voteTallier,printer);//create task
    }
    
    for(int j = 0; j < V; j++){
        delete voters[j];//task done
    }
    
}