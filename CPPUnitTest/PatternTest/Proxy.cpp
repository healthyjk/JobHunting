#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：代理设计模式测试用例
  * 作者：yanjiankang
  * 时间：2016年9月29日
  **/

class Subject {
public:
    virtual void request() = 0;
};

class RealSubject : public Subject {
public:
    void request() {
        LOG(INFO) << "RealSubject Operation";
    }
};

class ProxySubject {
public:
    ProxySubject() {
        //有人觉得 RealSubject对象的创建应该是在main中实现；我认为RealSubject应该
        //对用户是透明的，用户所面对的接口都是通过代理的；这样才是真正的代理；
        sub = new RealSubject();
    }

    ~ProxySubject() {
        if (NULL != sub) {
            delete sub;
            sub = NULL;
        }
    }

    void preRequest() {
        LOG(INFO) << "preRequest";
    }

    void postRequest() {
        LOG(INFO) << "postRequest";
    }

    void request() {
        sub->request();
    }
private:
    RealSubject* sub;
};

SUITE(ProxyPatternTest)
{
    TEST(Normal1)
    {
        ProxySubject* proxy = new ProxySubject();
        proxy->preRequest();
        proxy->request();
        proxy->postRequest();
        return;
    }
}
