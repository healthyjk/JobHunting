#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <queue>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：LeetCode刷题记录
  * 作者：yanjiankang
  * 时间：2016年10月3日
  **/

SUITE(LeetCodeTest2)
{
    class Solution {
    public:
        bool GetDistance(const string& s1, const string& s2) {
            int n = s1.size();
            int count = 0;
            for (int i = 0; i < n; ++i) {
                if (s1[i] != s2[i]) {
                    count++;
                }
            }
            return (count==1);
        }

        /*通过BFS遍历找到最短路径*/
        //通过BFS遍历找到最短路径
        int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
            if (beginWord == endWord) return 0;
            int min_count = 0;

            wordList.erase(beginWord);
            wordList.insert(endWord);
            int n = wordList.size();
            queue<string> q;
            q.push(beginWord);

            map<string, int> visit_map;

            for (auto it = wordList.begin(); it != wordList.end(); ++it) {
                visit_map[*it] = INT_MAX;
            }

            visit_map[beginWord] = 1;

            while (!q.empty()) {
                string word = q.front();
                q.pop();

                if (word == endWord) {
                    return visit_map[word];
                }

                string temp = word;
                for (int i = 0; i < word.size(); ++i) {
                    char c = temp[i];

                    for (int j = 0; j < 26; ++j) {
                        if (('a' + j) == c) continue;
                        temp[i] = 'a' + j;
                        if (wordList.find(temp) != wordList.end() && visit_map[temp] == INT_MAX) {
                            q.push(temp);
                            visit_map[temp] = visit_map[word] + 1;
                        }
                    }
                    temp[i] = c;
                }

                //cout << q.size() << endl;
            }
            return 0;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        string beginWord = "hit";
        string endWord = "cog";
        unordered_set<string> wordList = {"hot","dot","dog","lot","log"};
        int result = ladderLength(beginWord, endWord, wordList);
        cout << "distance:" << result << endl;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        string beginWord = "a";
        string endWord = "c";
        unordered_set<string> wordList = {"a","b","c"};
        int result = ladderLength(beginWord, endWord, wordList);
        cout << "distance:" << result << endl;
    }
}
