#ifndef __Q1_H__
#define __Q1_H__
#include <vector>
using namespace std;

_Coroutine Station {
    struct Frame {
        enum { Token, Data, Ack } type;                  // type of frame
        unsigned int src;                                // source id
        unsigned int dst;                                // destination id
        unsigned int prio;                               // priority
    } frame;
    
    unsigned int id;
    unsigned int num_Round;
    int reserve_prio;
    Station *nexthop;
    vector<unsigned int> round;
    vector<unsigned int> dst;
    vector<unsigned int> prio;
    static unsigned int requests;                        // total send requests (if needed)
    int search_Request(void);
    int search_Reserve(void);
    void data( Frame frame );                            // pass frame
    void main();                                         // coroutine main
public:
    Station( unsigned int id );
    ~Station();
    void setup( Station *nexthop );                      // supply next hop
    void sendreq( unsigned int round, unsigned int dst, unsigned int prio ); // store send request
    void start();                                        // inject token and start
}; // Station
#endif