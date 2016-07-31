// JINRITOUTIAO-FEMSCode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string days[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

string hourToString(char c) {
    string result;
    if (c >= '0' && c <= '9') {
        result.push_back('0');
        result.push_back(c);
    } else if (c >= 'A' && c<= 'J') {
        result.push_back('1');
        result.push_back((c - 'A' + '0'));
    } else if (c >= 'K' && c <= 'N') {
        result.push_back('2');
        result.push_back((c - 'K' + '0'));
    }
    return result;
}

string getDayAndHour(string& s1, string& s2) {
    string result;
    int n = s1.size();
    int m = s2.size();
    if (n <= 0 || m <= 0) return result;
    int count = 0, pos = 0;
    int j;
    for (int i = 0; i < n; ++i) {
        if (s1[i] >= 'A' && s1[i] <= 'G' || (count > 0 && s1[i] >= '0' && s1[i] <= '9')) {
            for (j = pos; j < m; ++j) {
                if (s1[i] == s2[j]) {
                    count++;
                    result.push_back(s1[i]);
                    if (count == 2) return result;
                    else {
                      pos = j+1;
                      break;
                    }
                }
            }
        }
    }
    return result;
}

string getMinute(string& s1, string& s2) {
    string result;
    int n = s1.size();
    int m = s2.size();
    if (n <= 0 || m <= 0) return result;
    n = n < m ? n : m;
    for (int i = 0; i < n; ++i) {
        if (s1[i] == s2[i] && ((s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= 'A' && s1[i] <= 'Z'))) {
            if (i < 10) { 
                result.push_back('0');
                result.push_back((i+'0'));
            } else if (i < 60) {
                result.push_back((i/10 + '0'));
                result.push_back((i%10 + '0'));
            }
            break;
        }
    }
    return result;
}

int main() {
    ifstream cin("input.txt");
    string s1, s2, s3, s4;
    while (cin >> s1 >> s2 >> s3 >> s4) {
        string result;
        string temp = getDayAndHour(s1, s2);
        if (temp.size() > 1) {
            result += days[(temp[0]-'A')];
            result.push_back(' ');
            result += hourToString(temp[1]);
        }
        result.push_back(':');
        result += getMinute(s3,s4);
        cout << result << endl;
    }
}
