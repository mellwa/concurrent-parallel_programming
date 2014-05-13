//----------------------------------------------------------
// using functor to simulate a resumption program
// this noresumption program does the exacly same task with
// the original one
//----------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

struct functor;//pre-define functor

void f(int &i, functor &a);// pre-define the function f

//----------------------------------------------------------
// a functor using to simulate the resume exception handler
//----------------------------------------------------------
struct functor{
public:
    int *i;
    functor *parent; // store a pointer of a functor in previous layer
    functor(int *b, functor* func){i = b; parent=func;}
    int operator()(){
      if(parent == NULL)
        cout<<"root"<<endl;
      else{// simulate the resume exception handler
        cout << "f handler " << *i << endl;
        *i -= 1;
        f(*i,*parent);
      }
    }
};//functor

//----------------------------------------------------------
// function passing a functor as an argument, so we can get
// the functor from previous recursive function (or say the
// functor on the previous stack)
//----------------------------------------------------------
void f(int &i, functor &a){
    functor b(&i,&a);
    int j = i;
    cout << "f " << i << endl;
    if ( rand() % 5 == 0 )
    {
        a();    // require correction ?
    }
        i -= 1;
        if ( 0 < i ) f( i, b );                             // recursion
}

int main(int argc, char** argv) {
    int times = 25, seed = getpid();
    switch ( argc ) {
        case 3: seed = atoi( argv[2] );                    // allow repeatable experiment
        case 2: times = atoi( argv[1] );                   // control recursion depth
        case 1: break;                                     // defaults
        default: cerr << "Usage: " << argv[0] << " times seed" << endl; exit( EXIT_FAILURE );
    }
    srand( seed );                                       // fixed or random seed

    functor a(&times,NULL);
    f(times,a);
}
