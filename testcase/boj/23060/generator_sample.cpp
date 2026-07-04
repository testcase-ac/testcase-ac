#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampCoord(int value, int n) {
  return min(max(value, 1), n);
}

pair<int, int> chooseStart(int n, int mode) {
  if (mode == 0) {
    vector<pair<int, int>> corners = {{1, 1}, {1, n}, {n, 1}, {n, n}};
    return rnd.any(corners);
  }

  if (mode == 1) {
    vector<pair<int, int>> edges;
    int samples = min(n, 8);
    for (int i = 1; i <= samples; ++i) {
      int x = 1 + (long long)(i - 1) * (n - 1) / max(1, samples - 1);
      edges.push_back({1, x});
      edges.push_back({n, x});
      edges.push_back({x, 1});
      edges.push_back({x, n});
    }
    return rnd.any(edges);
  }

  if (mode == 2) {
    int center = (n + 1) / 2;
    return {
        clampCoord(center + rnd.next(-2, 2), n),
        clampCoord(center + rnd.next(-2, 2), n),
    };
  }

  return {rnd.next(1, n), rnd.next(1, n)};
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int sizeMode = rnd.next(0, 5);
  int n;
  if (sizeMode == 0) {
    n = rnd.next(1, 4);
  } else if (sizeMode == 1) {
    n = rnd.next(5, 12);
  } else if (sizeMode == 2) {
    n = rnd.next(13, 40);
  } else if (sizeMode == 3) {
    n = rnd.next(41, 120);
  } else if (sizeMode == 4) {
    n = rnd.next(121, 499);
  } else {
    n = 500;
  }

  pair<int, int> start = chooseStart(n, rnd.next(0, 3));

  println(n);
  println(start.first, start.second);
  return 0;
}
