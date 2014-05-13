#include <iostream>
#include <fstream>
#include <limits>
#include "config.h"
using namespace std;

static bool comments(ifstream &in,string &name){
  for(;;){
    in>>name;
    if(in.fail()){
      return true;
    }
    if(name.substr(0,1)!="#"){
      break;
    }
    in.ignore(numeric_limits<int>::max(),'\n');
  }
  return false;
}

void processConfigFile(const char *configFile,ConfigParms &cparms){
  const unsigned int Parmnum=9;
  struct{
    const char *name;
    bool used;
    unsigned int *value;
  }static parms[Parmnum]={
    {"SodaCost",false,&cparms.sodaCost},
    {"NumStudents",false,&cparms.numStudents},
    {"MaxPurchases",false,&cparms.maxPurchases},
    {"NumVendingMachines",false,&cparms.numVendingMachines},
    {"MaxStockPerFlavour",false,&cparms.maxStockPerFlavour},
    {"MaxShippedPerFlavour",false,&cparms.maxShippedPerFlavour},
    {"TimeBetweenShipments",false,&cparms.timeBetweenShipments},
    {"ParentalDelay",false,&cparms.parentalDelay},
    {"NumCouriers",false,&cparms.numCouriers},
  };
  string name;
  unsigned int value,cnt,posn;
  unsigned int numOfParm=0;
  try{
    ifstream in(configFile);
    for(cnt=0;cnt<Parmnum;cnt+=1){
      if(comments(in,name)){
        break;
      }
      for(posn=0;posn<Parmnum&&name!=parms[posn].name;posn+=1){
      }
      if(posn==Parmnum){
        break;
      }
      if(parms[posn].used){
        break;
      }
      in>>value;
      if(in.fail()){
        break;
      }
      in.ignore(numeric_limits<int>::max(),'\n');
      numOfParm+=1;
      parms[posn].used=true;
      *parms[posn].value=value;
    }
    if(numOfParm !=Parmnum){
      cerr<<"Error: file \""<<configFile<<"\" is corrupt."<<endl;
      exit(EXIT_FAILURE);
    }
    if(!comments(in,name)){
      cerr<<"Error: file \""<<configFile<<"\" has extraneous data."<<endl;
      exit(EXIT_FAILURE);
    }
  }catch(uFile::Failure){
    cerr<<"Error: could not open input file \""<<configFile<<"\""<<endl;
    exit(EXIT_FAILURE);    
  }
}

