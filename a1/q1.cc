#include <iostream>
using namespace std;
#include <cstdlib>                                // exit, atoi

struct T {
    ~T() { cout << "~T" << endl;
    }
};
struct E {};
unsigned int hc, gc, fc, kc;

void f( volatile int i ) {                        // volatile, prevent dead-code optimizations
    T t;
    cout << "f enter" << endl;
  if ( i == 3 ) throw E();
    if ( i != 0 ) f( i - 1 );
    cout << "f exit" << endl;
    kc += 1;                                      // prevent tail recursion optimization
}
void g( volatile int i ) {
    cout << "g enter" << endl;
    if ( i % 2 == 0 ) f( fc );
    if ( i != 0 ) g( i - 1 );
    cout << "g exit" << endl;
    kc += 1;
}
void h( volatile int i ) {
    cout << "h enter" << endl;
    if ( i % 3 == 0 ) {
        try {
            f( fc );
        } catch( E ) {
            cout << "handler 1" << endl;
            try {
                g( gc );
            } catch( E ) {
                cout << "handler 2" << endl;
            }
        }
    }
    if ( i != 0 ) h( i - 1 );
    cout << "h exit" << endl;
    kc += 1;
} 
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
    h( hc );
}
 
