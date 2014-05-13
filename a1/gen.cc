#include <iostream>
using namespace std;


void uMain::main(){
    int seed = getpid();

    srand( seed );                                       // fixed or random seed
    
    for(int i = 0; i < 1000; i++){
        cout<<rand()%300<<" "<<rand()%300<<endl;
    }
    cout<<rand()<<" "<<rand();
    
}