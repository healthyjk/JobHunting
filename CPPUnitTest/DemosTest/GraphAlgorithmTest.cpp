#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"
#include "LinkGraph.hpp"

using namespace std;

/**
  * 测试用例：图相关算法测试；
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(GraphAlgorithmTest)
{
    TEST(Normal1)
    {
        vector<int> start = {1,1,2,6,6,3,3,7,7,4};
        vector<int> end = {2,5,6,7,3,7,4,8,4,8};
        LinkGraph graph(8);
        for (int i = 0 ; i < start.size(); ++i) {
            graph.AddDoubleEdge(start[i]-1, end[i]-1);
        }
        graph.BFS(1);
        graph.DFS();
        return;
    }

    TEST(Normal2)
    {
        vector<int> start = {1,1,2,6,6,3,3,7,7,4};
        vector<int> end   = {2,5,6,7,3,7,4,8,4,8};
        LinkGraph graph(8);
        for (int i = 0 ; i < start.size(); ++i) {
            graph.AddSingleEdge(start[i]-1, end[i]-1);
        }
        graph.TopologySort();
        graph.TopologySort_2();
        return;
    }
}

