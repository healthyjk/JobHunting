#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "State.h"

class Context {
public:
    Context();
    void changeState(State* state);
    void request();

private:
    State* state_;
};

#endif
