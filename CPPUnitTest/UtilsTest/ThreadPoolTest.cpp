#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "ThreadPool.h"
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：测试线程池
  * 作者：yanjiankang
  * 时间：2016年9月16日
  **/

SUITE(DemosTemplateTest)
{
    TEST(Normal1)
    {
        ThreadPool pool(4);
        std::vector< std::future<int> > results;

        for(int i = 0; i < 8; ++i) {
            results.emplace_back(
                pool.enqueue([i] {
                    LOG(INFO) << "hello " << i;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    LOG(INFO) << "world " << i;
                    return i*i;
                })
            );
        }

        for(auto && result: results)
            LOG(INFO) << result.get() << ' ';
        std::cout << std::endl;
        return;
    }
}
