#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：LeetCode刷题记录
  * 作者：yanjiankang
  * 时间：2016年10月3日
  **/

SUITE(DemosTemplateTest)
{
    class Solution {
    public:

        bool isMatch(string& str, int word_len, map<string, int>& word_map, vector<string>& words) {
            int n = str.size();
            map<string, int> count_map;

            for (int i = 0; i < n; i+= word_len) {
                string word = str.substr(i, word_len);
                if (word_map.find(word) == word_map.end()) {
                    return false;
                }
                count_map[word]++;
                if (count_map[word] > word_map[word]) {
                    return false;
                }
            }
            return true;
        }

        /*You are given a string, s, and a list of words, words, that are all of the same length.
         * Find all starting indices of substring(s) in s that is a concatenation of each word
         * in words exactly once and without any intervening characters.*/
        vector<int> findSubstring(string s, vector<string>& words) {
            vector<int> result;
            if (words.size() <= 0 || s.size() <= 0) return result;

            int word_len = words[0].size();
            int m = words.size();
            int n = s.size();
            int match_len = word_len * m;

            map<string, int> word_map;
            for (int j = 0; j < m; ++j) {
                word_map[words[j]]++;
            }

            for (int i = 0; i < n; ++i) {
                if ((i + match_len) > n) {
                    break;
                }

                string temp = s.substr(i, match_len);

                if (isMatch(temp, word_len, word_map, words)) {
                    result.push_back(i);
                }
            }

            return result;
        }

        /*Given a string of numbers and operators, return all possible results from
         * computing all the different possible ways to group numbers and operators.
         * The valid operators are +, - and *.*/
        vector<int> diffWaysToCompute(string input) {
            vector<int> result;
            int n = input.size();

            for (int i = 0; i < n; ++i) {
                if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
                    vector<int> left = diffWaysToCompute(input.substr(0, i));
                    vector<int> right = diffWaysToCompute(input.substr(i+1, n-i-1));

                    for(int j = 0; j < left.size(); ++j) {
                        for (int k = 0; k < right.size(); ++k) {
                            if (input[i] == '+') {
                                result.push_back((left[j] + right[k]));
                            } else if (input[i] == '-' ) {
                                result.push_back((left[j] - right[k]));
                            } else {
                                result.push_back((left[j] * right[k]));
                            }
                        }
                    }
                }
            }

            if (result.empty()) {
                result.push_back(atoi(input.c_str()));
            }

            return result;
        }

        /*Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
         * For example,Given n = 3, there are a total of 5 unique BST's.
         * 找到规律为： f[n] = f[0]*f[n-1]+f[1]*f[n-2]+...+f[n-2]*f[1]+f[n-1]*f[0], f[0]=1, f[1]=1;
         * 如果直接采用下一题一样的递归会直接超时；*/
        int numTrees(int n) {
            if (n <= 0) return 0;
            vector<int> fn(n+1, 0);
            fn[0] = 1;
            fn[1] = 1;
            for (int i = 2; i <= n; ++i) {
                computeFn(i, fn);
            }
            return fn[n];
        }

        void computeFn(int k, vector<int>& fn) {
            fn[k] = 0;
            for (int i = 0; i < k; ++i) {
                fn[k] += fn[i] * fn[k-1-i];
            }
        }

        /*Given an integer n, generate all structurally unique BST's (binary search trees)
         * that store values 1...n.
         * For example,Given n = 3, your program should return all 5 unique BST's shown below.
         * 此题采用递归的思路比较有技巧，应该学习*/

        vector<TreeNode*> generateTrees(int n) {
            vector<TreeNode*> result;
            if (n <= 0) return 0;
            return generateTrees(1, n);
        }

        vector<TreeNode*> generateTrees(int begin, int end) {
            vector<TreeNode*> result;
            if (begin <= end) {
                for (int i = begin; i <= end; ++i) {
                    vector<TreeNode*> left = generateTrees(begin, i-1);
                    vector<TreeNode*> right = generateTrees(i+1, end);
                    for (int j = 0; j < left.size(); ++j) {
                        for (int k = 0; k < right.size(); ++k) {
                            TreeNode* root = new TreeNode(i);
                            root->left = left[j];
                            root->right = right[k];
                            result.push_back(root);
                        }
                    }
                }
            } else {
                result.push_back(NULL);
            }
            return result;
        }

    };

    TEST_FIXTURE(Solution, Normal1)
    {
        string str = "wordgoodgoodgoodbestword";
        vector<string> words = {"word","good","best","good"};
        vector<int> result = findSubstring(str, words);
        for (int i = 0; i < result.size(); ++i) {
            LOG(INFO) << result[i];
        }
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
