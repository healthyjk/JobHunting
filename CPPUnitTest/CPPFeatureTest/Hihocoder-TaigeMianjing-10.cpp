#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：HihoCoder 太阁面经算法竞赛10
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(HihocderTaigeTenTemplateTest)
{
    class Solution {
    public:
        int bin2dec(const string& bin) {
            int n = bin.size();
            int result = 0;
            for (int i = n-1; i >= 0; --i) {
                result += (bin[i] == '0' ? 0 : (1 << (n-1-i)));
            }
            return result;
        }

        void timeToString(int hour, int minute, string& result) {
            result = "";
            result += (char)('0' + hour/10);
            hour = hour % 10;
            result += (char)('0' + hour);
            result += ':';
            result += (char)('0' + minute/10);
            minute = minute % 10;
            result += (char)('0' + minute);
        }

        bool binToHumanRead(string& binary, string& result) {
            if (binary.size() != 11) return false;
            int hour = bin2dec(binary.substr(0, 5));
            int minute = bin2dec(binary.substr(5, 6));
            if (minute >= 60 || hour >= 24) {
                return false;
            } else {
                timeToString(hour, minute, result);
                return true;
            }
            return false;
        }

        /*函数描述：枚举”1的个数为num_1, 0的个数为num_0“的所有排列组合，按从大到小的结果输出
          函数思路：首先在1的个数能够增长的时候一直增长；不能增长的时候在1前面插0；
          其中pos指示1的个数；*/
        void combine(int const num_1, int const num_0, vector<string>& result, int const pos = 0, string const str = ""){
            if (pos == num_1){
                result.push_back((str + string(num_0, '0')));
                cout << (str + string(num_0, '0')) << "\n";
            }
            else{
                for (int i = 0; i <= num_0; ++i){
                    combine(num_1, num_0 - i, result, pos + 1, str + string(i, '0') + '1');
                }
            }
        }


        /*二进制手表：其中x代表其中有几个1；（手表是5个时钟位+6个分钟位，有x位为1）
          分析:问题的本质就是有n位，其中x个1， n-x个0，列举出所有情况，对每个情况单独判断下就可以
          难点：问题的难点在于如何递归枚举所有情况，按一定的从小到大的顺序*/
        int BinaryWatch(int x)
        {
            vector<string> result;
            if (x == 0) {
                cout << "00:00" << endl;
                return 0;
            } else {
                combine(x, 11-x, result);
            }
            for (int i = result.size() - 1; i >= 0; --i) {
                string time;
                if (binToHumanRead(result[i], time)) {
                    cout << time << endl;
                }
            }
            result.clear();
            return 0;
        }

        /*题目描述：Given N lists of customer purchase,
         * your task is to find the products that appear in all of the lists.
         * A purchase list consists of several lines. Each line contains 3 parts:
         * the product id (format XXXX-XXXX), the purchase date (format mm/dd/yyyy)
         * and the price (with decimal places). Two product are considered equal
         * if both the product id and the price are equal.
         * 题目易错点：难点主要在于id可以重复，如果用multi-map比较复杂；
         * 因此我使用了id-price作为键值，id作为value，set存储id-price；*/
        string makeIdPrice(const string& id, double price) {
            ostringstream os;
            char a[20];
            sprintf(a, "%.2lf", price); //使用sprintf_s来进行double转换
            os << id << '-' << a;
            return os.str();
        }

        int PopularProduct(string filename)
        {
            ifstream cin(filename);
            int N;
            LOG(INFO) << "PopularProduct start";
            while (cin >> N) {
                unordered_set<string> ids;
                vector<unordered_map<string, string>> productMap(N);
                for (int i = 0; i < N; ++i) {
                    int m;
                    cin >> m;
                    for (int j = 0; j < m; ++j) {
                        string id, data;
                        double price;
                        cin  >> id >> data >> price;
                        string id_price = makeIdPrice(id, price);
                        productMap[i][id_price] = id;
                        ids.insert(id_price);
                    }
                }

                vector<string> result;
                for (auto iter = ids.begin(); iter != ids.end(); ++iter) {
                    int flag = true;
                    for (int i = 0; i < N; ++i) {
                        if (productMap[i].find((*iter)) == productMap[i].end()) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        result.push_back(productMap[0][*iter]);
                    }
                }

                sort(result.begin(), result.end());

                for (int i = 0; i < result.size(); ++i) {
                    cout << result[i] << endl;
                }
            }
            LOG(INFO) << "PopularProduct end";
            return 0;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        vector<string> result;
        combine(3, 4, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        PopularProduct("input_hihocoder_taige10_PopularProduct.txt");
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
