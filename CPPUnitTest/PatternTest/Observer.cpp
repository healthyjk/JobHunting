#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：观察者设计模式测试用例
  * 观察者模式：定义对象间的一种一对多依赖关系，使得每当一个对象状态发生改变时，其相关依赖对象皆得到通知并被自动更新。
  * 观察者模式又叫做发布-订阅（Publish/Subscribe）模式、模型-视图（Model/View）模式、源-监听器（Source/Listener）
  * 模式或从属者（Dependents）模式。
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

class Subject;
class Observer;


SUITE(ObverserTest)
{
    class Observer {
    public:
        virtual ~Observer() {}
        virtual void update() = 0;
        //virtual void update(Subject* sub) = 0;
    };

    class Subject {
    public:
        virtual ~Subject() {}
        virtual void attachObserver(Observer* observer) = 0;
        virtual void detachObserver(Observer* observer) = 0;
        virtual void NotifyAll() = 0;
        int getState() {return state_;}
        void setState(int state) {state_ = state;}
    protected:
        vector<Observer*> observers;
        int state_;
    };

    class ConcreteSubject : public Subject {
    public:
        void attachObserver(Observer* observer) {
            observers.push_back(observer);
        }

        void detachObserver(Observer* observer) {
            for (auto it = observers.begin(); it != observers.end(); ++it) {
                if (*it == observer) {
                    observers.erase(it);
                    break;
                }
            }
        }

        void NotifyAll() {
            for (auto it = observers.begin(); it != observers.end(); ++it) {
                //(*it)->update(this);
                (*it)->update();
            }
        }
    };

    class ConcreteObverser : public Observer{
    public:
        void update() {
        //void update(Subject* sub) {
            LOG(INFO) << "Subject has changed state to "; //<< sub->getState();
        }
    };

    TEST(Normal)
    {
        Observer* observer = new ConcreteObverser();
        Subject* subject = new ConcreteSubject();
        subject->attachObserver(observer);
        subject->NotifyAll();
        delete observer;
        delete subject;
        return;
    }
}
