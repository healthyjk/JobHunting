/*
 * =====================================================================================
 *
 *       Filename:  insertion_sort.cpp
 *
 *    Description:  insertion_sort
 *
 *        Version:  1.0
 *        Created:  2015年05月07日 21时36分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yan Jiankang (jkyan), jkyan@fudan.edu.cn
 *        Company:  Micro Systems, Fudan
 *
 * =====================================================================================
 */

#include <iostream>
using namespace std;

void insertion_sort(int* array, int len);

int main() {
	int len;
	cout << "Please input the length:" << endl;
	cin >> len;
	int array[len];
	cout << "Please input the numbers:" << endl;
	for (int i = 0; i < len; ++i) {
		cin >> array[i];
	}

	insertion_sort(array, len);

	for (int i = 0; i < len; ++i) {
		cout << array[i] << "\t";
	}
	cout << endl;
	return 0;
}

void insertion_sort(int* array, int len) {
	for (int i = 1; i < len; ++i) {
		/*
		for (int j = 0; j < i; ++j) { //此处顺序判断很傻，浪费时间
			if (array[j] > array[i]) {
				int temp = array[i];
				for (int k = i-1; k >= j; --k) {
					array[k+1] = array[k];
				}
				array[j] = temp;
				break;
			}
		} */

		int j = i - 1; //j每次都要重新赋值
		int temp = array[i];
		while ((j >= 0) && (array[j] > temp)) {
			array[j+1] = array[j];
			j--;
		}
		if (j != (i-1))
			array[j+1] = temp;
	}
}
