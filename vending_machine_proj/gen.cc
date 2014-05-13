#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;

class MPRNG {
  public:
    MPRNG( unsigned int seed = 1009 ) { srand( seed ); }// set seed
    void seed( unsigned int seed ) { srand( seed ); } // set seed
    unsigned int operator()() { return rand(); }  // [0,UINT_MAX]
    unsigned int operator()( unsigned int u ) { 
	return operator()() % (u + 1); 
    } // [0,u]
    unsigned int operator()( unsigned int l, unsigned int u ){ 
	return operator()( u - l ) + l; 
    } // [l,u]
};

MPRNG mprng;

int main(int argc, char **argv)
{
    mprng.seed(getpid());
    cout << "SodaCost\t\t"<<mprng(1,20)<<endl ;
    cout << "NumStudents\t\t"<<mprng(1,20)<<endl ;
    cout << "MaxPurchases\t\t"<<mprng(1,20)<<endl ;
    cout << "NumVendingMachines\t"<<mprng(1,20)<<endl ;
    cout << "MaxStockPerFlavour\t"<<mprng(1,20)<<endl ;
    cout << "MaxShippedPerFlavour\t"<<mprng(1,20)<<endl ;
    cout << "TimeBetweenShipments\t"<<mprng(1,20)<<endl ;
    cout << "ParentalDelay\t\t"<<mprng(1,20)<<endl ;
    cout << "NumCouriers\t\t"<<mprng(1,20)<<endl ;
    cout<<endl;
}

