#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(0, 5);
  int n;
  if (mode == 0) {
    n = rnd.next(2, 4);
  } else if (rnd.next(0, 9) == 0) {
    n = rnd.next(60, 300);
  } else {
    n = rnd.next(5, 35);
  }

  vector<pair<int, int>> edges;
  if (mode == 0) {
    for (int v = 2; v <= n; ++v) edges.push_back({v - 1, v});
  } else if (mode == 1) {
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
      if (v != center) edges.push_back({center, v});
    }
  } else if (mode == 2) {
    int pathLen = rnd.next(2, n);
    for (int v = 2; v <= pathLen; ++v) edges.push_back({v - 1, v});
    for (int v = pathLen + 1; v <= n; ++v) {
      int attach = rnd.next(1, pathLen);
      edges.push_back({attach, v});
    }
  } else if (mode == 3) {
    int spine = rnd.next(2, max(2, n / 2));
    for (int v = 2; v <= spine; ++v) edges.push_back({v - 1, v});
    for (int v = spine + 1; v <= n; ++v) {
      int attach = rnd.next(1, spine);
      edges.push_back({attach, v});
    }
  } else if (mode == 4) {
    for (int v = 2; v <= n; ++v) {
      int parent = max(1, v / 2 + rnd.next(-1, 1));
      parent = min(parent, v - 1);
      edges.push_back({parent, v});
    }
  } else {
    for (int v = 2; v <= n; ++v) {
      int parent = rnd.next(1, v - 1);
      edges.push_back({parent, v});
    }
  }

  vector<int> label(n + 1);
  iota(label.begin(), label.end(), 0);
  shuffle(label.begin() + 1, label.end());

  shuffle(edges.begin(), edges.end());

  println(n);
  for (auto [a, b] : edges) {
    if (rnd.next(0, 1)) swap(a, b);
    println(label[a], label[b]);
  }

  return 0;
}
