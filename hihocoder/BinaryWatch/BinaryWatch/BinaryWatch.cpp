// BinaryWatch.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int bin2dec(string& bin) {
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

void combine(int const num_1, int const num_0, vector<string>& result, int const pos = 0, string const str = ""){
    if (pos == num_1){
		result.push_back((str + string(num_0, '0')));
        //cout << (str + string(num_0, '0')) << "\n";
    }
    else{
        for (int i = 0; i <= num_0; ++i){
            combine(num_1, num_0 - i, result, pos + 1, str + string(i, '0') + '1');
        }
    }
}


int main()
{
	//ifstream cin("input.txt");
	int x; 
	vector<string> result;
	while (cin >> x) {
		if (x == 0) {
			cout << "00:00" << endl;
			continue;
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
	}
	return 0;
}

