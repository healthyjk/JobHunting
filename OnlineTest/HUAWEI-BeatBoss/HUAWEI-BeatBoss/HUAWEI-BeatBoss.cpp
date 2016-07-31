// HUAWEI-BeatBoss.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int BOSS_NORMAL_ATTACK = 10;
const int BOSS_CRITICAL_ATTACK = 30;
const int PLAYER_NORMAL_ATTACK = 17;
const int PLAYER_MAGIC_ATTACK = 60;
const int PER_MAGIC_CONSUME = 10;

inline int getBossAttack(const int rounds) {
  if (rounds > 1 && rounds % 4 == 1) {
    return BOSS_CRITICAL_ATTACK;
  } else {
    return BOSS_NORMAL_ATTACK;
  }
}

int fightRounds(int& php, int& pmp, int& bhp, int delta_php, int delta_pmp, int delta_bhp) {
  bhp -= delta_bhp;
  if (bhp <= 0) {
    return 1;
  }

  pmp -= delta_pmp;
  php -= delta_php;
  if (php <= 0) {
    return -1;
  }
  return 0;
}

int computeMinRounds(int php, int pmp, int bhp) {
  int rounds = 1;
  while (true) {
    // magic attack
    while (pmp >= 10) {
      int temp = fightRounds(php, pmp, bhp, getBossAttack(rounds), 
        PER_MAGIC_CONSUME, PLAYER_MAGIC_ATTACK);
      if (temp == 1) {
        return rounds;
      }
      if (temp == -1) {
        return -1;
      }
      rounds++;
    }

    //basic attack or magic restore
    while (true) {
      int n = 2;
      if ((pmp + (n << 2)) < 10) {
        n = 3;
      }

      if (bhp < ((n+1) * PLAYER_NORMAL_ATTACK)) {
        while (true) {
          int temp = fightRounds(php, pmp, bhp, getBossAttack(rounds), 
            0, PLAYER_NORMAL_ATTACK);
          if (temp == 1) {
            return rounds;
          }
          if (temp == -1) {
            return -1;
          }
          rounds++;
        }
      } else if ((PLAYER_MAGIC_ATTACK/(n+1)) > PLAYER_NORMAL_ATTACK) {
        for (int i = 0; i < n; ++i) {
          int temp = fightRounds(php, pmp, bhp, getBossAttack(rounds), 
            -4, 0);
          if (temp == 1) {
            return rounds;
          }
          if (temp == -1) {
            return -1;
          }
          rounds++;
        }
        break;
      } else {
        int temp = fightRounds(php, pmp, bhp, getBossAttack(rounds), 
            0, PLAYER_NORMAL_ATTACK);
        if (temp == 1) {
          return rounds;
        }
        if (temp == -1) {
          return -1;
        }
        rounds++;
        continue;
      }
    }
  }
}


int main() {
  ifstream cin("input.txt");
  int php, pmp, bhp;
  while (cin >> php >> pmp >> bhp) {
    int rounds = computeMinRounds(php, pmp, bhp);
    cout << rounds << endl;
  }

  return 0;
}
