// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

const int maxn = 10001;
int n, m;
bool f[maxn];

int main()
{
	ifstream cin("input.txt");
	cin >> n >> m;
	f[0] = true;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		for (int j = maxn - 1; j >= x; j--)
			f[j] |= f[j - x];
	}

	for (int i = m; i < maxn; i++)
		if (f[i])
		{
			printf("%d\n", i);
			return 0;
		}
	puts("-1");
}

