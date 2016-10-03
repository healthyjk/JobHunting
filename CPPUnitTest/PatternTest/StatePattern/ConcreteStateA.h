#ifndef _CONCRETESTATE_A_H_
#define _CONCRETESTATE_A_H_

#include "Context.h"
#include "state.h"

class ConcreteStateA : public State {
public:
    static ConcreteStateA* getInstance();
    static void destoryInstance();
    void handle(Context *context);

    /*构造垃圾回收类*/
    class CGarbge {
    public:
        ~CGarbge() {
            //ConcreteStateA::destoryInstance();
        }
    };

private:
    ConcreteStateA() {}
    ConcreteStateA(const ConcreteStateA&) = delete;
    ConcreteStateA& operator =(const ConcreteStateA&) = delete;
    static ConcreteStateA* m_state_a_;
    static CGarbge cgarbge;
};



#endif
