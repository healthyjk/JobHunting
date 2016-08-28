#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <map>
#include <fstream>


using namespace std;

/**
  * 测试用例：Hihocder 太阁面经竞赛 9
  * 参考解法：http://hihocoder.com/discuss/question/2154
  * 题目描述：在浏览网页的时候，缓存技术能够迅速地显示页面。这里我们对浏览器的缓存技术进行简化：
  * 我们认为浏览器的缓存大小为M，表示缓存可以存储M个页面。
  * 当用户访问URL时，浏览器会先到缓存中查询是否有该页面的记录，如果有则直接从缓存中提取数据；
  * 否则，会发送网络请求，从Internet获取该页面，并将该页面放入缓存中。当缓存中的页面数量超过M时，
  * 缓存技术会替换掉缓存中最不频繁访问的网页，即最后访问时间最早的页面。现在，我们希望对于给定的用户访问历史记录，
  * 请判断出每一次访问页面是从缓存中读取的，还是通过网络请求获得的。(缓存最开始数据为空)
  *
  * 解题思路：首先我们用a[1..n]来表示浏览网页的记录，用map< url, int > lastVisit的方式来对URL进行记录。
  * lastVisit[ a[i] ]表示a[i]这条url最后一次访问时对应的时间。
  * 我们知道缓存的大小为M，而且满足了缓存中一定是M个不相同的URL。
  * 假设在我们现在的缓存中最早的一条记录对应的为a[s]，最新的一条记录对应的是a[t]。
  * t一定总是等于i的，因为a[i]一定是最新的访问记录。而对于s，我们一定有 lastVisit[ a[s] ] == s。
  * 因为若lastVisit[ a[s] ] = k，则一定有k>s，表示该URL在[s+1,t]之中仍存在。若lastVisit[ a[s] ] = s，
  * 则表示在[s+1,t]这个区间内都没有a[i]的访问记录了，a[s]则一定是[s,t]这个区间中最早的访问记录。
  *
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(HihocoderTaiGeNineTemplateTest)
{
    class Solution {
    public:
        map<string, int> lastVisited;

        vector<bool> BrowserCache(const vector<string>& pages, int n, int m) {
            vector<bool> result;
            int start = 1;
            int cache_cnt = 0;

            for (int i = 1; i <= n; ++i) {
                if (lastVisited[pages[i]] >= start && lastVisited[pages[i]] <= i) {
                    result.push_back(true);
                } else {
                    result.push_back(false);

                    cache_cnt++;
                    if (cache_cnt > m) {
                        start = start + 1;
                    }
                }
                lastVisited[pages[i]] = i;
                while (lastVisited[pages[start]] != start) {
                    start = start + 1;
                }
            }

            return result;
        }

        int BrowserCacheSolution(string filename)
        {
            ifstream cin(filename);
            int n, m;
            while (cin >> n >> m) {
                vector<string> inputs(n+1);
                for (int i = 1; i <= n; ++i) {
                    cin >> inputs[i];
                }
                vector<bool> result = BrowserCache(inputs, n, m);
                for (int i = 0; i < n; ++i) {
                    if (result[i]) {
                        cout << "Cache" << endl;
                    } else {
                        cout << "Internet" << endl;
                    }
                }
            }
            return 0;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        vector<string> input = {"", "www.bing.com", "www.microsoft.com", "www.microsoft.com", "windows.microsoft.com", "www.bing.com"};
        vector<bool> result = BrowserCache(input, 5, 2);
        CHECK_EQUAL(true, result[2]);
        CHECK_EQUAL(false, result[4]);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
