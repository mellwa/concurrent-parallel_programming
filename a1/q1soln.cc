//-----------------------------------------------------
// rewrite a throw/catch program by using longjmp/setjmp
// to simulate same performance except one aspect
//-----------------------------------------------------
#include <iostream>
using namespace std;
#include <cstdlib>
#include <setjmp.h>// exit, atoi

struct T {
    ~T() {
        cout << "~T" << endl;
    }
};//T
jmp_buf env;
unsigned int hc,gc,fc,kc;

void f( volatile int i );
void g( volatile int i );
void h( volatile int i );

void f( volatile int i ) {
    T t;
    cout << "f enter" << endl;
    if ( i == 3 ) longjmp(env,1);//do a long jump if i is equal to 3
    if ( i != 0 ) f( i - 1 );
    cout << "f exit" << endl;
    kc += 1;                       // prevent tail recursion optimization
}//f
void g( volatile int i ) {
    cout << "g enter" << endl;
    if ( i % 2 == 0 ) f( fc );
    if ( i != 0 ) g( i - 1 );
    cout << "g exit" << endl;
    kc += 1;
}//g
void h( volatile int i ) {
    cout << "h enter" << endl;
    if(setjmp(env)==1){ // set a jump point
        cout << "handler 1" << endl;
        if(setjmp(env)==1){ // set a jump point
            cout << "handler 2" << endl;
        }
        else{
            g(gc);
        }
    }else{
        f(fc);
    }
    if ( i != 0 ) h( i - 1 );
    cout << "h exit" << endl;
    kc += 1;
}//h

int main( int argc, char *argv[] ) {
    switch ( argc ) {
        case 4: fc = atoi( argv[3] );               // f recursion depth
        case 3: gc = atoi( argv[2] );               // g recursion depth
        case 2: hc = atoi( argv[1] ); break;        // h recursion depth
        default: cerr << "Usage: " << argv[0] << " hc gc fc" << endl;
            exit( EXIT_FAILURE );
    }
    if ( hc < 0 || gc < 0 || fc < 0 ) {
        cerr << "Input less than 0" << endl;
        exit( EXIT_FAILURE );
    }
    h(hc);
    return 0;
}//main
