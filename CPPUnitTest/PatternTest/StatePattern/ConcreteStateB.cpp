
#include "EasyLogging/easylogging++.h"
#include <iostream>
#include "ConcreteStateB.h"
#include "ConcreteStateA.h"

ConcreteStateB* ConcreteStateB::m_state_b_;
ConcreteStateB::CGarbge ConcreteStateB::cgarbge;

ConcreteStateB* ConcreteStateB::getInstance() {
    if (NULL == m_state_b_) {
        m_state_b_ = new ConcreteStateB();
    }
    return m_state_b_;
}

void ConcreteStateB::destoryInstance() {
    if (NULL != m_state_b_) {
        delete m_state_b_;
    }
}

void ConcreteStateB::handle(Context *context) {
    LOG(INFO) << "doing something in State B.\n done,change state to A";
    context->changeState(ConcreteStateA::getInstance());
}
