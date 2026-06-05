#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

int NextWeight(int mode, int idx) {
  if (mode == 0) return rnd.next(1, 20);
  if (mode == 1) return 100000 - rnd.next(0, 200);
  if (mode == 2) return idx % 2 == 0 ? rnd.next(1, 10) : rnd.next(99900, 100000);
  return rnd.next(1, 100000);
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int n = rnd.next(3, 14);
  int maxEdges = n * (n - 1) / 2;
  int mode = rnd.next(0, 4);
  int m = rnd.next(n, min(maxEdges, n + rnd.next(0, n)));

  vector<int> vertices(n);
  iota(vertices.begin(), vertices.end(), 1);
  shuffle(vertices.begin(), vertices.end());

  set<pair<int, int>> used;
  vector<tuple<int, int, int>> edges;

  auto addEdge = [&](int a, int b, int w) {
    if (a > b) swap(a, b);
    if (used.insert({a, b}).second) {
      edges.emplace_back(a, b, w);
    }
  };

  if (mode == 0) {
    for (int i = 1; i < n; ++i) {
      addEdge(vertices[i - 1], vertices[i], NextWeight(mode, i));
    }
  } else if (mode == 1) {
    int center = vertices[0];
    for (int i = 1; i < n; ++i) {
      addEdge(center, vertices[i], NextWeight(mode, i));
    }
  } else if (mode == 2) {
    int split = rnd.next(1, n - 2);
    for (int i = 1; i <= split; ++i) {
      addEdge(vertices[i - 1], vertices[i], NextWeight(mode, i));
    }
    for (int i = split + 2; i < n; ++i) {
      addEdge(vertices[i - 1], vertices[i], NextWeight(mode, i));
    }
    addEdge(vertices[0], vertices[split + 1], NextWeight(mode, n));
  } else {
    for (int i = 1; i < n; ++i) {
      int parent = rnd.next(0, i - 1);
      addEdge(vertices[parent], vertices[i], NextWeight(mode, i));
    }
  }

  vector<pair<int, int>> candidates;
  for (int a = 1; a <= n; ++a) {
    for (int b = a + 1; b <= n; ++b) {
      if (!used.count({a, b})) candidates.push_back({a, b});
    }
  }
  shuffle(candidates.begin(), candidates.end());

  int edgeIdx = n;
  for (auto [a, b] : candidates) {
    if ((int)edges.size() >= m) break;
    addEdge(a, b, NextWeight(mode, edgeIdx++));
  }

  shuffle(edges.begin(), edges.end());

  int q = rnd.next(1, min(25, n * (n - 1) / 2));
  vector<pair<int, int>> queries;
  for (int a = 1; a <= n; ++a) {
    for (int b = a + 1; b <= n; ++b) {
      queries.push_back({a, b});
    }
  }
  shuffle(queries.begin(), queries.end());

  println(n, (int)edges.size());
  for (auto [a, b, w] : edges) {
    if (rnd.next(0, 1)) swap(a, b);
    println(a, b, w);
  }
  println(q);
  for (int i = 0; i < q; ++i) {
    auto [x, y] = queries[i];
    if (rnd.next(0, 1)) swap(x, y);
    println(x, y);
  }

  return 0;
}
