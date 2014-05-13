#ifndef _AUTOMATICSIGNAL_H_
#define _AUTOMATICSIGNAL_H_

#define AUTOMATIC_SIGNAL uCondition bench

#define WAITUNTIL(pred, before, after){ \
    if(!pred){ \
        before; \
        bench.wait(); \
        after;  \
    } \
    if(!bench.empty()){bench.signal();} \
}

#define RETURN(expr...){ \
    return expr; \
}


#endif