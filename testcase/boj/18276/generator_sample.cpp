#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
  int u;
  int v;
  long long w;
};

long long chooseWeight(int pattern, int index, int n) {
  if (pattern == 0) return rnd.next(1, 20);
  if (pattern == 1) return 1;
  if (pattern == 2) return 1000000000LL - rnd.next(0, 25);
  if (pattern == 3) return (index % 2 == 0) ? rnd.next(1, 5) : rnd.next(15, 40);
  if (pattern == 4) return max(1, n - index) + rnd.next(0, 3);
  return rnd.next(1, 1000000000);
}

void relabelAndShuffle(int n, vector<Edge>& edges) {
  vector<int> label(n + 1);
  for (int i = 1; i <= n; ++i) label[i] = i;
  shuffle(label.begin() + 1, label.end());

  for (auto& edge : edges) {
    edge.u = label[edge.u];
    edge.v = label[edge.v];
    if (rnd.next(2) == 0) swap(edge.u, edge.v);
  }
  shuffle(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(0, 5);
  int n = rnd.next(2, 14);
  int weightPattern = rnd.next(0, 5);
  vector<Edge> edges;

  if (mode == 0) {
    for (int i = 2; i <= n; ++i) {
      edges.push_back({i - 1, i, chooseWeight(weightPattern, i - 2, n)});
    }
  } else if (mode == 1) {
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
      if (i != center) {
        edges.push_back({center, i, chooseWeight(weightPattern, i, n)});
      }
    }
  } else if (mode == 2) {
    int spine = rnd.next(2, n);
    for (int i = 2; i <= spine; ++i) {
      edges.push_back({i - 1, i, chooseWeight(weightPattern, i - 2, n)});
    }
    for (int i = spine + 1; i <= n; ++i) {
      edges.push_back({rnd.next(1, spine), i, chooseWeight(weightPattern, i - 2, n)});
    }
  } else if (mode == 3) {
    for (int i = 2; i <= n; ++i) {
      edges.push_back({i / 2, i, chooseWeight(weightPattern, i - 2, n)});
    }
  } else {
    for (int i = 2; i <= n; ++i) {
      edges.push_back({rnd.next(1, i - 1), i, chooseWeight(weightPattern, i - 2, n)});
    }
  }

  relabelAndShuffle(n, edges);

  println(n);
  for (const auto& edge : edges) {
    println(edge.u, edge.v, edge.w);
  }
  return 0;
}
