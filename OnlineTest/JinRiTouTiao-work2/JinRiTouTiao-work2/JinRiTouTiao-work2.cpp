// JinRiTouTiao-work2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool CompFunc(const pair<long long,int>& p1, const pair<long long, int>& p2) {
    return p1.first > p2.first;
}

void setLetterNumMap(vector<long long>& counts, unordered_map<char, int>& letter_num, vector<bool>& flags) {
    vector<pair<long long, int>> count_index; 
    for (int i = 0; i < 10; ++i) {
        count_index.push_back(make_pair(counts[i], i));
        cout << "i:" << i << "--" << counts[i] << endl;
    }
    sort(count_index.begin(), count_index.end(), CompFunc);

    int i = 9;
    if (flags[count_index[i].second]) {
        int j = i-1;
        while (j>=0 && flags[count_index[j].second]) {
          j--;
        }
        if (j>=0) {          
          /*for (int k = 9; k>j;--k) {
            count_index[k].first = count_index[k-1].first;
          }*/
          count_index[j].first = 0;
          sort(count_index.begin(), count_index.end(), CompFunc);
        }
    }

    for (int i = 0; i < 10; ++i) {
        letter_num.insert(make_pair((count_index[i].second+'A'), 9-i));
    }
}

long long strToLong(string& str, unordered_map<char, int>& lettermap) {
  long long result = 0;
  for (int i = 0; i < str.size(); ++i) {
    result = result*10 + lettermap[str[i]];
  }
  return result;
}

long long computerMaxSum(vector<string>& strs, unordered_map<char, int>& letter_num) {
    long long sum = 0;
    int n = strs.size();
    for (int i = 0; i < n; ++i) {
        sum += strToLong(strs[i], letter_num);
    }
    return sum;
}

int main() {
    int n;
    ifstream cin("input.txt");
    while (cin >> n) {
        vector<string> strs(n);
        for (int i = 0; i < n; ++i) {
            cin >> strs[i];
        }
        
        vector<long long> counts(10, 0);
        vector<bool> flags(10, false);
        int len;
        long long weight;
        for (int i = 0; i < n; ++i) {
            len = strs[i].size();
            weight = 1;
            for (int j = len-1; j >= 0; --j) {
                counts[(strs[i][j]-'A')] += weight;
                weight *= 10;
            }
            flags[(strs[i][0]-'A')] = true;
        }
        
        unordered_map<char, int> letter_num;
        setLetterNumMap(counts, letter_num, flags);
        
        for (unordered_map<char, int>::iterator iter = letter_num.begin(); iter != letter_num.end(); ++iter) {
          cout << iter->first << "__" << iter->second << endl;
        }

        long long result = computerMaxSum(strs, letter_num);
        
        cout << result << endl;
    }
    return 0;
}
