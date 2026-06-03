#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int COORD_MAX = 100000000;

int nearby(int center, int radius) {
  int lo = max(0, center - radius);
  int hi = min(COORD_MAX, center + radius);
  return rnd.next(lo, hi);
}

void addStick(vector<pair<int, int>>& sticks, set<pair<int, int>>& used, int t,
              int d) {
  pair<int, int> stick = {t, d};
  if (used.insert(stick).second) {
    sticks.push_back(stick);
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(0, 5);
  int l;
  if (mode == 5) {
    l = rnd.any(vector<int>{1, 2, 999999, 1000000});
  } else {
    l = rnd.next(1, 1000000);
  }

  vector<pair<int, int>> sticks;
  set<pair<int, int>> used;

  if (mode == 0) {
    int t = rnd.any(vector<int>{0, 1, COORD_MAX - 1, COORD_MAX});
    int d = rnd.any(vector<int>{0, 1, COORD_MAX - 1, COORD_MAX});
    addStick(sticks, used, t, d);
  } else if (mode == 1) {
    int n = rnd.next(4, 18);
    int base = rnd.next(0, 1000);
    int spread = rnd.next(0, 30);
    for (int i = 0; i < n; ++i) {
      addStick(sticks, used, nearby(base, spread), nearby(base, spread));
    }
  } else if (mode == 2) {
    int topCount = rnd.next(2, 7);
    int bottomCount = rnd.next(2, 7);
    vector<int> top, bottom;
    int start = rnd.next(0, 200);
    int step = rnd.next(1, 20);
    for (int i = 0; i < topCount; ++i) {
      top.push_back(start + i * step);
    }
    for (int i = 0; i < bottomCount; ++i) {
      bottom.push_back(start + rnd.next(0, 10) + i * rnd.next(1, 20));
    }
    for (int t : top) {
      for (int d : bottom) {
        if (rnd.next(0, 99) < 45) {
          addStick(sticks, used, t, d);
        }
      }
    }
  } else if (mode == 3) {
    int n = rnd.next(6, 24);
    int base = rnd.next(0, 5000);
    for (int i = 0; i < n; ++i) {
      int t = base + i * rnd.next(1, 9);
      int d = base + (n - 1 - i) * rnd.next(1, 9);
      addStick(sticks, used, t, d);
    }
  } else if (mode == 4) {
    int n = rnd.next(8, 32);
    vector<int> anchors = {0, 1, 2, COORD_MAX - 2, COORD_MAX - 1, COORD_MAX};
    for (int i = 0; i < n; ++i) {
      int t = rnd.any(anchors);
      int d = rnd.any(anchors);
      addStick(sticks, used, t, d);
    }
  } else {
    int n = rnd.next(20, 80);
    int topBase = rnd.next(0, COORD_MAX - 1000);
    int bottomBase = rnd.next(0, COORD_MAX - 1000);
    for (int i = 0; i < n; ++i) {
      int t = topBase + rnd.next(0, 1000);
      int d = bottomBase + rnd.next(0, 1000);
      addStick(sticks, used, t, d);
    }
  }

  while (sticks.empty()) {
    addStick(sticks, used, rnd.next(0, COORD_MAX), rnd.next(0, COORD_MAX));
  }

  shuffle(sticks.begin(), sticks.end());

  println(static_cast<int>(sticks.size()), l);
  for (auto stick : sticks) {
    println(stick.first, stick.second);
  }

  return 0;
}
