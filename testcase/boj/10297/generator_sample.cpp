#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
  vector<pair<int, int>> edges;
  for (int i = 1; i < n; ++i) edges.push_back({i, i + 1});
  return edges;
}

vector<pair<int, int>> makeStar(int n) {
  vector<pair<int, int>> edges;
  for (int i = 2; i <= n; ++i) edges.push_back({1, i});
  return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
  vector<pair<int, int>> edges;
  for (int v = 2; v <= n; ++v) {
    int parent = rnd.next(1, v - 1);
    edges.push_back({parent, v});
  }
  return edges;
}

vector<pair<int, int>> makeBroom(int n) {
  vector<pair<int, int>> edges;
  int handle = rnd.next(1, n);
  for (int i = 1; i < handle; ++i) edges.push_back({i, i + 1});
  for (int v = handle + 1; v <= n; ++v) edges.push_back({handle, v});
  return edges;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int t = rnd.next(1, 10);
  println(t);

  for (int tc = 0; tc < t; ++tc) {
    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    if (tc == 0 && rnd.next(0, 3) == 0) n = 1;

    vector<pair<int, int>> edges;
    if (mode == 0) {
      edges = makePath(n);
    } else if (mode == 1) {
      edges = makeStar(n);
    } else if (mode == 2) {
      edges = makeBroom(n);
    } else {
      edges = makeRandomTree(n);
    }
    shuffle(edges.begin(), edges.end());

    vector<int> x(n);
    int valueMode = rnd.next(0, 5);
    for (int i = 0; i < n; ++i) {
      if (valueMode == 0) {
        x[i] = rnd.next(-8, 8);
      } else if (valueMode == 1) {
        x[i] = rnd.next(-9999, 9999);
      } else if (valueMode == 2) {
        x[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 40);
      } else if (valueMode == 3) {
        x[i] = rnd.next(-50, -1);
      } else {
        x[i] = rnd.next(0, 50);
      }
    }

    vector<int> safe(n);
    int safeMode = rnd.next(0, 5);
    for (int i = 0; i < n; ++i) {
      if (safeMode == 0) {
        safe[i] = 1;
      } else if (safeMode == 1) {
        safe[i] = (i == 0 || i == n - 1);
      } else if (safeMode == 2) {
        safe[i] = (i % 2 == 0);
      } else if (safeMode == 3) {
        safe[i] = 0;
      } else {
        safe[i] = rnd.next(0, 1);
      }
    }

    println(n);
    for (auto [a, b] : edges) {
      if (a > b) swap(a, b);
      println(a, b);
    }
    println(x);
    println(safe);
  }

  return 0;
}
