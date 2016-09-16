#ifndef __SINGLETON_H_
#define __SINGLETON_H_

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/*使用模版方式实现的单例模式*/
template <class T>
class TemplateSingleTon {
public:
    template<typename... Args>
    static T* instance(Args&&... args) {
        if (NULL == mInstance_) {
            mInstance_ = new T(std::forward<Args>(args)...);
        }
        return mInstance_;
    }

    static T* getInstance() {
        return mInstance_;
    }

    static void destoryInstance() {
        if (nullptr != mInstance_) {
            delete mInstance_;
            mInstance_ = NULL;
        }
    }

private:
    TemplateSingleTon() = delete;
    TemplateSingleTon(const TemplateSingleTon&) = delete;
    TemplateSingleTon& operator=(const TemplateSingleTon) = delete;
    static T* mInstance_;
};

template<class T>
T* TemplateSingleTon<T>::mInstance_ = NULL;


/*懒汉方式实现单例模式，静态成员实例实现*/
class SingleTon_Lazy1 {
public:
    /*这种方式并不是绝对线程安全的，因此new操作分为以下三步：
      1. 分配内存空间
      2. 在该内存空间上构造对象
      3. 将内存空间的地址赋值给指针
      其中2，3步的顺序不能保证，可能导致其他线程拿到了未构造完全的对象的地址*/
    static SingleTon_Lazy1* getInstance() {
        if (mInstance_ == NULL) {
            lock_guard<mutex> lock_(mtx_);
            if (mInstance_ == NULL) {
                mInstance_ = new SingleTon_Lazy1();
            }
        }
        return mInstance_;
    }

    static void destoryInstance() {
        if (NULL != mInstance_) {
            lock_guard<mutex> lock_(mtx_);
            delete mInstance_;
            mInstance_ = NULL;
        }
    }

private:
    SingleTon_Lazy1() {}
    ~SingleTon_Lazy1() {}
    SingleTon_Lazy1(const SingleTon_Lazy1&) = delete;
    SingleTon_Lazy1& operator =(const SingleTon_Lazy1&) = delete;
    static SingleTon_Lazy1* mInstance_;
    static mutex mtx_;

    /*使用内部类来保证单例类在结束时自动释放内存*/
    class CGarbo {
    public:
        ~CGarbo() {
            if (NULL != SingleTon_Lazy1::mInstance_) {
                delete SingleTon_Lazy1::mInstance_;
                SingleTon_Lazy1::mInstance_ = NULL;
                cout << "CGarbo: delete SingleTon_Hungry" << endl;
            } else {
                cout << "CGarbo: SingleTon_Hungry has deleted" << endl;
            }
        }
    };

    static CGarbo cgarbo; /*必须在外部声明，否则不会构造*/
};

SingleTon_Lazy1* SingleTon_Lazy1::mInstance_ = NULL;
mutex SingleTon_Lazy1::mtx_;
SingleTon_Lazy1::CGarbo SingleTon_Lazy1::cgarbo;


/*懒汉方式实现单例模式,使用内部静态变量，C++11下保证线程安全，但是C++0X不保证*/
class SingleTon_Lazy2 {
public:
    static SingleTon_Lazy2* getInstance() {
        lock_guard<mutex> lock(mtx_);
        static SingleTon_Lazy2 instance;
        return &instance;
    }

private:
    SingleTon_Lazy2() {}
    ~SingleTon_Lazy2() {}
    SingleTon_Lazy2(const SingleTon_Lazy2&) = delete;
    SingleTon_Lazy2& operator =(const SingleTon_Lazy2&) = delete;
    static mutex mtx_;
};

mutex SingleTon_Lazy2::mtx_;

/*饿汉单例模式：即无论是否调用该类的实例，在程序开始时就会产生一个该类的实例，并在以后仅返回此实例。*/
class SingleTon_Hungry {
public:
    static const SingleTon_Hungry* getInstance() {
        return mInstance_;
    }

    static const SingleTon_Hungry* destoryInstance() {
        if (NULL != mInstance_) {
            delete mInstance_;
            mInstance_ = NULL;
        }
    }

private:
    SingleTon_Hungry() {}
    SingleTon_Hungry(const SingleTon_Hungry&) = delete;
    SingleTon_Hungry& operator =(const SingleTon_Hungry&) = delete;
    static const SingleTon_Hungry* mInstance_;
};

const SingleTon_Hungry* SingleTon_Hungry::mInstance_ = new SingleTon_Hungry();

/*C++11下使用callonce实现的单例模式*/
class SingleTon_C11 {

};



#endif
