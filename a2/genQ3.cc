#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


int main(){
    srand(200);
    int num = 0;
    num = rand()%500000;
    cout<<num;
    for(int i = 0; i< num; i++){
        cout<<" "<<rand()%500000;
    }
    cout<<endl;
    
    num = rand()%1000000;
    cout<<num;
    for(int i = 0; i< num; i++){
        cout<<" "<<rand()%1000000;
    }
    cout<<endl;
    
    num = rand()%5000000;
    cout<<num;
    for(int i = 0; i< num; i++){
        cout<<" "<<rand()%5000000;
    }
    cout<<endl;
    
    num = rand()%2000000;
    cout<<num;
    for(int i = 0; i< num; i++){
        cout<<" "<<(0-rand()%2000000);
    }
    cout<<endl;
    
    return 0;
}