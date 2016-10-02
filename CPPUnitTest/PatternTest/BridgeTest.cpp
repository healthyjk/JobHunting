#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <string>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：桥接模式
  * 设计模式介绍：桥接模式(Bridge Pattern)：将抽象部分与它的实现部分分离，使它们都可以独立地变化。
  * 它是一种对象结构型模式，又称为柄体(Handle and Body)模式或接口(Interface)模式。
  * 作者：yanjiankang
  * 时间：2016年9月16日
  **/

class Implementation {
public:
    virtual void operationImpl() {
        LOG(INFO) << "BaseI mplementation!";
    }
};

class ImplementationA : public Implementation {
public:
    void operationImpl() {
        LOG(INFO) << "A mplementation!";
    }
};

class ImplementationB : public Implementation {
public:
    void operationImpl() {
        LOG(INFO) << "B mplementation!";
    }
};

class Abstration {
public:
    Abstration(Implementation* implementation) {
        implementation_ = implementation;
    }

    virtual ~Abstration() {
        if (NULL != implementation_) {
            delete implementation_;
        }
    }

    void operation(){
        implementation_->operationImpl();
    }

protected:
    Implementation* implementation_;
};

class RefinedAbstration : public Abstration {
public:
    RefinedAbstration(Implementation* impl) : Abstration(impl)  {}

    void operation(){
        LOG(INFO) << "do something else, and then";
        implementation_->operationImpl();
    }
};


/*以下为桥接模式应用实例*/
class OS {
public:
    OS() {}

    virtual void install() {
        LOG(INFO) << "Install OS";
    }
};

class PC {
public:
    PC(OS* os) {
        os_ = os;
    }

    ~PC() {
       if (NULL != os_) {
           delete os_;
       }
    }

    void installOS() {
        LOG(INFO) << getPCType();
        os_->install();
    }

    virtual string getPCType() {
        string type("Normal PC");
        return type;
    }

public:
    OS* os_;
};

class WindowsOS : public OS {
public:
    virtual void install() {
        LOG(INFO) << "Install Windows OS";
    }
};

class LinuxOS : public OS {
public:
    virtual void install() {
        LOG(INFO) << "Install Linux OS";
    }
};

class HP_PC : public PC {
public:
    HP_PC(OS* os) : PC(os) {}
    string getPCType() {
        string type("HP PC");
        return type;
    }
};

SUITE(BridgeTest)
{
    TEST(Normal1)
    {
        Implementation* impl = new ImplementationA();
        RefinedAbstration* refineAbs_a = new RefinedAbstration(impl);

        Implementation* imp2 = new ImplementationB();
        RefinedAbstration* refineAbs_b = new RefinedAbstration(imp2);

        refineAbs_a->operation();
        refineAbs_b->operation();
        delete refineAbs_a;
        delete refineAbs_b;
        delete impl;
        delete imp2;
    }

    TEST(Normal2) {
        OS* winos = new WindowsOS();
        HP_PC* hp = new HP_PC(winos);
        hp->installOS();
        delete winos;
        delete hp;
    }
}
