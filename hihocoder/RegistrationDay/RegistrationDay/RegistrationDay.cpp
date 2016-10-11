// RegistrationDay.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

struct Student {
  int id;
  int arrival;
  int office_num;
  int end_time;
  vector<int> seq_office;
  vector<int> seq_time;
  int process_count;

  Student() : process_count(0) {}
};

struct Event {
  int arrival_time;
  int student_index;
  int student_id;
  int process_time;
  int office_id;
  
  Event(int arr, int index, int sid, int p_time, int o_id) : arrival_time(arr), student_index(index), student_id(sid), process_time(p_time), office_id(o_id) {}

  /*�¼�Ĭ�ϰ�����ʱ�����򣬵���ʱ����ͬ��ѧ������*/
  /*ע�⣺Ĭ�����ȼ����������ѣ���������Ҫ��С�ѣ�����less������Ϊ�෴����*/
  bool operator < (const Event& e) const {
    if (e.arrival_time > arrival_time) return false;
    if (e.arrival_time < arrival_time) return true;
    return (e.student_id < student_id);
  }
};


int main() {
  ifstream cin("input.txt");
  int n, m, k;
  while (cin >> n >> m >> k) {
    vector<Student> students(n);
    priority_queue<Event> q;

    for (int i = 0; i < n; ++i) {
      cin >> students[i].id >> students[i].arrival >> students[i].office_num;
      students[i].arrival += k;
      for (int j = 0; j < students[i].office_num; ++j) {
        int num, time;
        cin >> num >> time;
        students[i].seq_office.push_back(num);
        students[i].seq_time.push_back(time);
      }
      q.push(Event(students[i].arrival, i, students[i].id, students[i].seq_time[students[i].process_count], students[i].seq_office[students[i].process_count]));
    }

    /*��¼��ǰ�칫�Ҵ����¼���ĵ�ǰʱ��*/
    vector<int> cur_time(m, 0);

    while (!q.empty()) {
      Event e = q.top();
      q.pop();
      int index = e.student_index;
      int oid = e.office_id - 1;
      Student& stu = students[index];

      if (stu.arrival < cur_time[oid]) {
        stu.arrival = cur_time[oid];
      }

      stu.process_count++;
      stu.arrival += e.process_time;
      cur_time[oid] = stu.arrival;

      int next_office_index = stu.process_count;

      /*������������һ���칫�ң���ǰѧ������*/
      if (next_office_index == stu.office_num) {
        continue;
      }

      stu.arrival += k; /*ѧ��������һ���칫�ң������µ���һ�������¼�*/
      Event next(stu.arrival, index, stu.id, stu.seq_time[next_office_index], stu.seq_office[next_office_index]);
      q.push(next);
    }

    for (int i = 0; i < n; ++i) {
      cout << students[i].arrival << endl;
    }

  }

  return 0;
}

