#ifndef _CONCRETESTATE_B_H_
#define _CONCRETESTATE_B_H_

#include "Context.h"
#include "state.h"

class ConcreteStateB : public State {
public:
    static ConcreteStateB* getInstance();
    static void destoryInstance();
    void handle(Context *context);

    /*构造垃圾回收类*/
    class CGarbge {
    public:
        ~CGarbge() {
            //ConcreteStateB::destoryInstance();
        }
    };

private:
    ConcreteStateB() {}
    ConcreteStateB(const ConcreteStateB&) = delete;
    ConcreteStateB& operator =(const ConcreteStateB&) = delete;
    static ConcreteStateB* m_state_b_;
    static CGarbge cgarbge;
};



#endif
