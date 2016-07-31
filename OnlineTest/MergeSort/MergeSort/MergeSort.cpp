// MergeSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <malloc.h>

#define INT_MAX 2147483647

using namespace std;

void merge_sort(int* array, int begin, int end);
void merge(int* array, int begin, int middle, int end);
void merge_no_guard(int* array, int begin, int middle, int end);
void printArray(int* array, int len);
void merge_sort_iter(int *list, int length);

int main() {
  //int len;
  //cout << "Please input the length:" << endl;
  //cin >> len;
  //int* array = new int[len];

  /*cout << "Please input the numbers:" << endl;
  for (int i = 0; i < len; ++i) {
  cin >> array[i];
  }*/

  int array[] = {1, 7 ,2, 9 ,4, 0, 3};
  int len = sizeof(array)/sizeof(int);
  
  //merge_sort(array, 0, len-1);
  merge_sort_iter(array, len);

  for (int i = 0; i < len; ++i) {
    cout << array[i] << "\t";
  }
  cout << endl;

  //delete[] array;
  system("pause");
  return 0;
}

void merge_sort(int* array, int begin, int end) {
  if (begin >= end) return;
  int middle = (int)((end+begin)/2.0);
  merge_sort(array, begin, middle);
  merge_sort(array, middle+1, end);
  merge_no_guard(array, begin, middle, end);
}


/*有哨兵时,当排序数中出现INT_MAX时会出现错误*/
void merge(int* array, int begin, int middle, int end) {
  cout << "merge:" << begin << "," << middle << "," << end << endl;
  if (begin >= end) return;
  int left_len = middle - begin + 1;
  int right_len = end - middle;
  int* left = new int[left_len+1];
  int* right = new int[right_len+1];
  int i = 0;
  for (i = 0; i < left_len; ++i) {
    left[i] = array[begin+i];
  }		
  left[i] = INT_MAX;
  for (i = 0; i < right_len; ++i) {
    right[i] = array[middle+1+i];
  }
  right[i] = INT_MAX;
  int k = 0;
  int l = 0;
  for (i = 0; i < (right_len+left_len); ++i) {
    if (left[k]<right[l]) {
      array[begin+i] = left[k];
      k++;
    } else {
      array[begin+i] = right[l];
      l++;
    }
  }
  delete left;
  delete right;
}

//无哨兵
void merge_no_guard(int* array, int begin, int middle, int end) {
  cout << "merge:" << begin << "," << middle << "," << end << endl;
  if (begin >= end) return;
  int left_len = middle - begin + 1;
  int right_len = end - middle;
  int* left = new int[left_len];
  int* right = new int[right_len];
  int i = 0;
  for (i = 0; i < left_len; ++i) {
    left[i] = array[begin+i];
  }		
  for (i = 0; i < right_len; ++i) {
    right[i] = array[middle+1+i];
  }
  int k = 0;
  int l = 0;
  i = 0;
  while (k < left_len && l < right_len) {
    if (left[k]<right[l]) {
      array[begin+i] = left[k];
      k++;
    } else {
      array[begin+i] = right[l];
      l++;
    }
    i++;
  }
  if (k != left_len) {
    for (l = k; l < left_len; ++l) {
      array[begin+i] = left[l];
      i++;
    }
  }
  if (l != right_len) {
    for (k = l; k < right_len; ++k) {
      array[begin+i] = right[k];
      i++;
    }
  }
  delete left;
  delete right;

  for (int i =begin; i <= end; ++i) {
    cout << array[i] << "\t";
  }
  cout << endl;
}

void printArray(int* array, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%d\t", array[i]);
  }
  printf("\n");
}



// merge_sort(): 非递归实现-自底向上
// 将原数组划分为left[min...max] 和 right[min...max]两部分
void merge_sort_iter(int *list, int length)
{
  int i, left_min, left_max, right_min, right_max, next;
  int *tmp = (int*)malloc(sizeof(int) * length);

  if (tmp == NULL)
  {
    fputs("Error: out of memory\n", stderr);
    abort();
  }

  for (i = 1; i < length; i *= 2) // i为步长，1,2,4,8……
  {
    for (left_min = 0; left_min < length - i; left_min = right_max)
    {
      right_min = left_max = left_min + i;
      right_max = left_max + i;

      if (right_max > length)
        right_max = length;

      next = 0;
      while (left_min < left_max && right_min < right_max)
        tmp[next++] = list[left_min] > list[right_min] ? list[right_min++] : list[left_min++];

      while (left_min < left_max)
        list[--right_min] = list[--left_max];

      while (next > 0)
        list[--right_min] = tmp[--next];
    }
  }

  free(tmp);

}

