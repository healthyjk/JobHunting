
#include "Context.h"
#include "ConcreteStateA.h"

Context::Context() {
    state_ = ConcreteStateA::getInstance();
}

void Context::changeState(State* state) {
    state_ = state;
}

void Context::request() {
    state_->handle(this);
}
