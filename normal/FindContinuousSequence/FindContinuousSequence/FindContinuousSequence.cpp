// FindContinuousSequence.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> > results;
        if (sum <= 2) return results;
        
        int low = 2;
        int high = sqrt(sum << 1);
        
        int temp;
        int a;
        for (int i = high; i >= low; --i) {
            temp = i * i - i;
            if (temp % 2 != 0) {
                continue;
            } 
           	
            temp = sum - (temp >> 1);
            if (temp % i != 0) {
                continue;
            }
            
            a = temp / i;
            if (a < 1) {
                continue;
            }
            
            vector<int> result;
            for (int j = 0; j < i; ++j) {
                result.push_back(a+j);
            }
            
           	results.push_back(result);
        }
        
        return results;
    }
};

int main()
{
  Solution solution;
  int sum = 0;
  while (cin >> sum) {
    vector<vector<int> > results = solution.FindContinuousSequence(sum);

    for (int i = 0; i < results.size(); ++i) {
      vector<int> result = results[i];
      for (int j = 0; j < result.size(); ++j) {
        cout << result[j] << "\t";
      }
      cout << endl;
    }
  }
	return 0;
}

