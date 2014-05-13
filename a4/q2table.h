#ifndef _Q2TABLE_H_
#define _Q2TABLE_H_

_Monitor Printer;

#if defined( TABLETYPE_SEM )                // semaphore solution
// includes for this kind of table
#include <uSemaphore.h>
class Table {
    // private declarations for this kind of table
private:
    uSemaphore *sem;
    uSemaphore *sem_barging;
    uSemaphore **sem_fork;
    bool *phil_is_eating;
#elif defined( TABLETYPE_INT )              // internal scheduling monitor solution
    // includes for this kind of table
    _Monitor Table {
        // private declarations for this kind of table
        uCondition *forks;
        bool *fork_is_occupied;
#elif defined( TABLETYPE_INTB )             // internal scheduling monitor solution with barging
        // includes for this kind of table
        _Monitor Table {
            // private declarations for this kind of table
            uCondition noforks;               // only one condition variable (you may change the variable name)
            bool *phil_is_eating;
            int waiting_phils;
            int signaled_phils;
            void wait();                            // barging version of wait
            void signalAll();
#else
#error unsupported table
#endif
            // common declarations
        private:
            Printer &printer;
            unsigned int NoOfPhil;
            unsigned int LeftPhil(unsigned int id);
            unsigned int RightPhil(unsigned int id);
        public:                                   // common interface
            Table( const unsigned int NoOfPhil, Printer &prt );
            void pickup( unsigned int id );
            void putdown( unsigned int id );
            ~Table();
        };


#endif