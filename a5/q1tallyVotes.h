#ifndef _Q1VALLYVOTES_H_
#define _Q1VALLYVOTES_H_

_Monitor Printer;



#if defined( IMPLTYPE_EXT )                    // external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_INT )                  // internal scheduling monitor solution
    // includes for this kind of vote-tallier
    _Monitor TallyVotes {
        // private declarations for this kind of vote-tallier
        uCondition cv;
#elif defined( IMPLTYPE_INTB )                 // internal scheduling monitor solution with barging
        // includes for this kind of vote-tallier
        _Monitor TallyVotes {
            // private declarations for this kind of vote-tallier
            uCondition bench;                          // only one condition variable (you may change the variable name)
            int signalled_voters;
            int waiting_voters;
            void wait();                               // barging version of wait
            void signalAll();                          // unblock all waiting tasks
#elif defined( IMPLTYPE_AUTO )                 // automatic-signal monitor solution
            // includes for this kind of vote-tallier
#include "AutomaticSignal.h"
            _Monitor TallyVotes {
                // private declarations for this kind of vote-tallier
                AUTOMATIC_SIGNAL;
                void Block_task(unsigned int id);
                void Unblock_task(unsigned int id);
#elif defined( IMPLTYPE_TASK )                 // internal/external scheduling task solution
                _Task TallyVotes {
                    // private declarations for this kind of vote-tallier
                    uCondition bench;
                    unsigned int tmp_taskid;
                    bool pregroupdone;
                    void main();
#else
#error unsupported voter type
#endif
                    // common declarations
                    unsigned int group;
                    Printer &printer;
                    int outcome;
                    unsigned int vote_members;
                    unsigned int blocked;
                public:                                     // common interface
                    TallyVotes( unsigned int group, Printer &printer );
                    ~TallyVotes();
                    bool vote( unsigned int id, bool ballot );
                };

                
#endif
                
