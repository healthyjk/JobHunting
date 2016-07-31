// JinRiTouTiao-work4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


int sameSectionInString(string& str) {
  int n = str.size();
  bool flag;
  for (int i = 1; i < n; ++i) {
    if (n % i != 0) continue;
    string temp = str.substr(0,i);
    flag = true;
    for (int j = i; j < n; j += i) {
      if (temp != str.substr(j, i)) {
        flag = false;
        break;
      }
    }
    if (flag) {
      return (n/i);
    }
  }
  return 1;
}

//template<typename BidiIt>
//bool nextPermutation(BidiIt first, BidiIt last) {
//  // Get a reversed range to simplify reversed traversal.
//  const auto rfirst = reverse_iterator<BidiIt>(last);
//  const auto rlast = reverse_iterator<BidiIt>(first);
//  // Begin from the second last element to the first element.
//  auto pivot = next(rfirst);
//  // Find `pivot`, which is the first element that is no less than its
//  // successor. `Prev` is used since `pivort` is a `reversed_iterator`.
//  while (pivot != rlast && *pivot >= *prev(pivot))
//    ++pivot;
//  // No such elemenet found, current sequence is already the largest
//  // permutation, then rearrange to the first permutation and return false.
//  if (pivot == rlast) {
//    reverse(rfirst, rlast);
//    return false;
//  }
//  // Scan from right to left, find the first element that is greater than
//  // `pivot`.
//  auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
//  swap(*change, *pivot);
//  reverse(rfirst, pivot);
//  return true;
//}

vector<vector<int> > permute(vector<int> &num) {
  vector<vector<int> > result;
  sort(num.begin(), num.end());
  do {
    result.push_back(num);
  } while(next_permutation(num.begin(), num.end()));
  return result;
}


int main() {

  ifstream cin("input.txt");
  int n, k;
  cin >> n >> k;
  vector<string> strs(n);
  for (int i = 0; i < n; ++i) {
    cin >> strs[i];
  }
  vector<int> seq(n, 0);
  for (int i = 0; i < n; ++i) {
    seq[i] = i;
  }

  vector<vector<int>> seqs = permute(seq);

  int result = 0;
  for (int i = 0; i < seqs.size(); ++i) {
    vector<int>& temp = seqs[i];
    int m = temp.size();
    string tempStr;
    for (int j = 0; j < m; ++j) {
      tempStr += strs[temp[j]];
    }
    int sections = sameSectionInString(tempStr);
    if (sections == k) {
      result++;
    }
  }

  cout << result << endl;

  return 0;
}
