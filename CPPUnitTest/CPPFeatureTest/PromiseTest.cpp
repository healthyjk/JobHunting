#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：Promise测试用例
  * 作者：yanjiankang
  * 时间：2016年10月6日
  **/
SUITE(PromiseTest)
{
    void print_int(std::future<int>& fut) {
        int x = fut.get();
        LOG(INFO) << "value:" << x;
    }

    TEST(Normal1)
    {
        std::promise<int> prom;
        std::future<int> fut = prom.get_future();
        std::thread t(print_int, std::ref(fut));
        prom.set_value(10);
        t.join();
        return;
    }
}
