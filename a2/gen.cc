#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(){
    int round, src, dst, prio;
    srand(300);
    for(int i = 0; i < 5000; i++){
        round = rand()%200;
        src = rand()%100;
        dst = rand()%100;
        prio = rand()%100;
        cout<<round<<" "<<src<<" "<<dst<<" "<<prio<<endl;
    }
    cout<<round<<" "<<src<<" "<<dst<<" "<<prio;
    return 0;
}