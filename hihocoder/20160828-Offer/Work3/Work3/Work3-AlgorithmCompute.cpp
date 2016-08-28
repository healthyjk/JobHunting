
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;

string equal_delim = "=";
string plus_delim = "+";

void split(string& s, string& delim, vector<string>& ret)  
{  
  size_t last = 0;  
  size_t index=s.find_first_of(delim,last);  
  while (index!=std::string::npos)  
  {  
    ret.push_back(s.substr(last,index-last));  
    last=index+1;  
    index=s.find_first_of(delim,last);  
  }  
  if (index-last>0)  
  {  
    ret.push_back(s.substr(last,index-last));  
  }  
}


long long TwoNumPlus(int a_len, int b_len, long long sum) {
	long long a_min = (long long)pow(10, a_len-1);
	long long a_max = (long long)pow(10, a_len) - 1;
	long long b_min = (long long)pow(10, b_len-1);
	long long b_max = (long long)pow(10, b_len) - 1;

	if (a_min > sum || b_min > sum || (a_min == sum && b_len > 1) 
		|| (b_min == sum && a_len > 1)) {
		return 0;
	}

	long long count = 0;
	for (long long i = a_min; i <= a_max; ++i) {
		long long temp = sum - i;
		if (temp >= b_min && temp <= b_max) {
			count++;
			cout << i << "+" << temp << "=" << sum << endl;
		}
		if (i > sum) break;
	}

	return count;
}

long long ThreeNumPlus(int a_len, int b_len, int c_len, long long sum) {
	long long a_min = (long long)pow(10, a_len-1);
	long long a_max = (long long)pow(10, a_len) - 1;
	long long b_min = (long long)pow(10, b_len-1);
	long long b_max = (long long)pow(10, b_len) - 1;
	long long c_min = (long long)pow(10, c_len-1);
	long long c_max = (long long)pow(10, c_len) - 1;

	if (a_min > sum || b_min > sum || c_min > sum || (a_min == sum && (b_len > 1 || c_len > 1)) 
		|| (b_min == sum && (a_len > 1 || c_len > 1)) || (c_min == sum && (a_len > 1 || b_len > 1))) {
		return 0;
	}

	long long count = 0;
	for (long long i = a_min; i <= a_max; ++i) {
		if (i > sum) break;
		for (long long j = b_min; j <= b_max && i+j <= sum; ++j) {
			long long temp = sum - i - j;
			if (temp >= c_min && temp <= c_max) {
				count++;
				//cout << i << "+" << j << "+" << temp << "=" << sum << endl;
			}
		}
		
	}

	return count;
}


int main()
{
	ifstream cin("input.txt");

	string s;
	while (cin >> s) {

		vector<string> temp1;
		split(s, equal_delim, temp1);
		if (temp1.size() != 2) {
			cout << '0' << endl;
			continue;
		}
		long long sum = 0;
		for (int i = 0; i < temp1[1].size(); ++i) {
			sum = sum * 10 + (temp1[1][i] - '0');
		}


		vector<string> temp2; 
		split(temp1[0], plus_delim, temp2);
		if (temp1.size() < 2) {
			cout << '0' << endl;
			continue;
		}

		vector<int> num_len;
		for (int i = 0; i < temp2.size(); ++i) {
			num_len.push_back(temp2[i].size());
		}

		long long count;
		if (num_len.size() == 2) {
			count = TwoNumPlus(num_len[0], num_len[1], sum);
		}

		if (num_len.size() == 3) {
			count = ThreeNumPlus(num_len[0], num_len[1], num_len[2], sum);
		}
		
		count %= 1000000007;

		cout << count << endl;
	}

	return 0;
}
