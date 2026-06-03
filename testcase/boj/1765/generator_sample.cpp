#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(0, 4);
  int n;
  if (mode == 0) {
    n = rnd.next(2, 8);
  } else if (mode == 1) {
    n = rnd.next(8, 18);
  } else if (mode == 2) {
    n = rnd.next(12, 30);
  } else if (mode == 3) {
    n = rnd.next(30, 80);
  } else {
    n = rnd.next(2, 1000);
  }

  vector<int> side(n + 1);
  if (mode == 0) {
    for (int i = 1; i <= n; ++i) side[i] = i % 2;
  } else if (mode == 1) {
    int split = rnd.next(1, n - 1);
    for (int i = 1; i <= n; ++i) side[i] = i > split;
  } else {
    for (int i = 1; i <= n; ++i) side[i] = rnd.next(0, 1);
    side[1] = 0;
    side[n] = 1;
  }

  vector<pair<int, int>> pairs;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      pairs.push_back({i, j});
    }
  }
  shuffle(pairs.begin(), pairs.end());

  int pair_count = static_cast<int>(pairs.size());
  int target;
  if (mode == 0) {
    target = rnd.next(1, min(pair_count, n + 2));
  } else if (mode == 1) {
    target = rnd.next(n - 1, min(pair_count, 2 * n));
  } else if (mode == 2) {
    target = rnd.next(n, min(pair_count, 4 * n));
  } else if (mode == 3) {
    target = rnd.next(40, min(pair_count, 220));
  } else {
    target = rnd.next(1, min(pair_count, 5000));
  }

  vector<tuple<char, int, int>> facts;
  facts.reserve(target);

  if (mode == 1) {
    for (int i = 1; i < n && static_cast<int>(facts.size()) < target; ++i) {
      char relation = side[i] == side[i + 1] ? 'F' : 'E';
      facts.push_back({relation, i, i + 1});
    }
  }

  for (auto [p, q] : pairs) {
    if (static_cast<int>(facts.size()) == target) break;
    bool already_used = false;
    for (auto [relation, used_p, used_q] : facts) {
      if (used_p == p && used_q == q) {
        already_used = true;
        break;
      }
    }
    if (already_used) continue;

    char relation = side[p] == side[q] ? 'F' : 'E';
    facts.push_back({relation, p, q});
  }

  shuffle(facts.begin(), facts.end());

  println(n);
  println(static_cast<int>(facts.size()));
  for (auto [relation, p, q] : facts) {
    println(relation, p, q);
  }
}
