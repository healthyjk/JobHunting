// RegistrationDay.cpp : 定义控制台应用程序的入口点。
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

  /*事件默认按到达时间排序，到达时间相同按学号排序*/
  /*注意：默认优先级队列是最大堆，因此如果想要最小堆，定义less操作符为相反即可*/
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

    /*记录当前办公室处理事件后的当前时间*/
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

      /*如果处理完最后一个办公室，当前学生结束*/
      if (next_office_index == stu.office_num) {
        continue;
      }

      stu.arrival += k; /*学生到达下一个办公室，构造新的下一个到达事件*/
      Event next(stu.arrival, index, stu.id, stu.seq_time[next_office_index], stu.seq_office[next_office_index]);
      q.push(next);
    }

    for (int i = 0; i < n; ++i) {
      cout << students[i].arrival << endl;
    }

  }

  return 0;
}

