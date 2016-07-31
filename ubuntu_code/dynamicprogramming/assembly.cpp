#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void PrintPath(int *, int , int);
void FastestWay(int *, int *, int [], int [], int);

int main(void) {
	int enterTimes[2] = {1, 2};
	int exitTimes[2] = {2, 1};
	int assemblyTimes[2][5] = {
		{4, 2, 3, 5, 3},
		{7, 2, 4, 2, 4}};
	int transferTimes[2][5] = {
		{2, 1, 2, 2, 1},
		{1, 1, 2, 4, 2}};

	FastestWay(&assemblyTimes[0][0], &transferTimes[0][0], enterTimes, exitTimes, 5);

	exit(0);
}

void FastestWay(int *assemblyTimes,
		int *transferTimes,
		int enterTimes[2],
		int exitTimes[2],
		int n) {
	int fastestTime = 0;
	int exitLine;
	int j;
	int* fastest;
	int* lineTag;
	int temp1, temp2;

	fastest = new int[2 * n];
	lineTag = new int[2 * n];

	*(fastest) = enterTimes[0] + *assemblyTimes;
	*(fastest + n) = enterTimes[1]
		+ *(assemblyTimes + n);
	for (j = 1; j < n; j++) {
		temp1 = *(fastest + (j-1));
		temp2 = *(fastest + (n + j - 1))
			+ *(transferTimes + (n + j - 1));
		if (temp1 <= temp2) {
			*(fastest + j) = temp1 + *(assemblyTimes + j);
			*(lineTag + j) = 1;
		} else {
			*(fastest + j) = temp2 + *(assemblyTimes + j);
			*(lineTag + j) = 2;
		}

		temp1 = *(fastest + (n + j - 1));
		temp2 = *(fastest + (j - 1)) + *(transferTimes + (j - 1));
		if (temp1 <= temp2) {
			*(fastest + (n + j)) = temp1 + *(assemblyTimes + (n + j));
			*(lineTag + (n + j)) = 2;
		} else {
			*(fastest + (n + j)) = temp2 + *(assemblyTimes + (n + j));
			*(lineTag + (n + j)) = 1;
		}
	}

	temp1 = *(fastest + (n - 1)) + exitTimes[0];
	temp2 = *(fastest + (n + n - 1)) + exitTimes[1];
	if (temp1 <= temp2) {
		fastestTime = temp1;
		exitLine = 1;
	} else {
		fastestTime = temp2;
		exitLine = 2;
	}

	printf("The cost of the fastest path: %d\n", fastestTime);
	PrintPath(lineTag, exitLine, n);

	delete lineTag;
	delete fastest;
}

void PrintStation(int line, int station) {
	printf("line: %d, station: %d\n", line, station);
}

void PrintPath(int *lineTag, int exitLine, int n) {
	int i = exitLine;
	int j;

	PrintStation(exitLine, 5);
	for (j = 5; j >= 2; j--)
	{
		i = *(lineTag + (n * (i - 1) + j - 1));
		PrintStation(i, j-1);
	}
}
