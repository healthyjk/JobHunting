#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：适配器模式测试
  * 作者：yanjiankang
  * 时间：2016年9月16日
  **/

class Target {
public:
    virtual ~Target() {}
    virtual void request() {
        LOG(INFO) << "Request operation...";
    }
};

class Adaptee {
public:
    void wrapRequest() {
        LOG(INFO) << "WrapRequest operation...";
    }
};

/*对象适配器：适配器类继承了目标抽象类并定义了一个适配者类的对象实例，
 * 在所继承的目标抽象类方法中调用适配者类的相应业务方法。*/
class Adapter : public Target {
public:
    Adapter(Adaptee* adaptee) {
        this->adaptee_ = adaptee;
    }

    ~Adapter() {
        if (NULL != adaptee_) {
            delete adaptee_;
        }
    }

    void request() {
        adaptee_->wrapRequest();
    }

private:
    Adaptee* adaptee_;
};

/*类适配器：适配器类实现了目标抽象类接口并继承了适配者类，
 * 并在目标抽象类的实现方法中调用所继承的适配者类的方法*/
class Adapter_Class : public Target, public Adaptee{
public:
    void request() {
        wrapRequest();
    }
    ~Adapter_Class() {}
};

SUITE(AdapterTest)
{
    TEST( Normal1)
    {
        Target* target = new Adapter(new Adaptee());
        target->request();
        delete target;
        return;

        Target* target2 = new Adapter_Class();
        target2->request();
        delete target2;
    }
}
