#ifndef _Q2TALLYVOTES_H_
#define _Q2TALLYVOTES_H_

_Monitor Printer;

#if defined( IMPLTYPE_MC )           // mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes {
    // private declarations for this kind of vote-tallier
private:
    uOwnerLock* olk;
    uCondLock* clk_blocking;
    uCondLock* clk_barging;
    bool barging;
#elif defined( IMPLTYPE_SEM )        // semaphore solution
    // includes for this kind of vote-tallier
#include <uSemaphore.h>
    class TallyVotes {
    private:
        uSemaphore* sem;
        uSemaphore* sem_barging;
        uSemaphore* sem_group;
        bool barging;
        // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_BAR )        // barrier solution
#include <uBarrier.h>
        // includes for this kind of vote-tallier
        _Cormonitor TallyVotes : public uBarrier {
            // private declarations for this kind of vote-tallier

#else
#error unsupported voter type
#endif
            // common declarations
            unsigned int blocked;//number of blocked tasks
            unsigned int group;//number of members in each group
            Printer &printer;
            int outcome;
            unsigned int vote_members;
        public:                            // common interface
            TallyVotes( unsigned int group, Printer &printer );
            bool vote( unsigned int id, bool ballot );
            ~TallyVotes();
        };


#endif