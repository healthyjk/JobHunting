
#include "stdafx.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>
using namespace std;

int data[1005];
int N, M, L;

bool Check(queue<int> q, int count)
{
    while ((q.empty() == false) && (count>0))
    {
        int start = q.front();
        while ((q.empty() == false) && (q.front() < start + L))
            q.pop();
        count--;
    }
    if (q.empty() == true)
        return true;
    else
        return false;
}

bool CheckFirst(int num)
{
    queue<int> q;
    for (int i = 0; i < N; i++)
    {
        if (data[i] < num)
            q.push(i);
    }
    while ((q.empty() == false) && (q.front() <= L))
    {
        if (Check(q, M))
            return true;
        q.push(q.front() + N);
        q.pop();
        if (Check(q, M))
            return true;
    }
    return Check(q, M);
}

int main()
{
    ifstream cin("input.txt");
	int Highest = 0;
    cin >> N >> M >> L;
    for (int i = 0; i < N; i++)
    {
        cin >> data[i];
        Highest = max(Highest, data[i]);
    }
    int start = 0, end = Highest + 1;
    while (start < end - 1)
    {
        int mid = (start + end) >> 1;
        if (CheckFirst(mid))
        {
            start = mid;
        }
        else
        {
            end = mid;
        }
    }
    cout << start << endl;
    return 0;
}
