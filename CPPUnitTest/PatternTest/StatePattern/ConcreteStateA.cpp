
#include "EasyLogging/easylogging++.h"
#include <iostream>
#include "ConcreteStateA.h"
#include "ConcreteStateB.h"

ConcreteStateA* ConcreteStateA::m_state_a_;
ConcreteStateA::CGarbge ConcreteStateA::cgarbge;

ConcreteStateA* ConcreteStateA::getInstance() {
    if (NULL == m_state_a_) {
        m_state_a_ = new ConcreteStateA();
    }
    return m_state_a_;
}

void ConcreteStateA::destoryInstance() {
    if (NULL != m_state_a_) {
        delete m_state_a_;
    }
}

void ConcreteStateA::handle(Context *context) {
    LOG(INFO) << "doing something in State A.\n done,change state to B";
    context->changeState(ConcreteStateB::getInstance());
}
