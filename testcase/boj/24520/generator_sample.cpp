#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
  int u;
  int v;
  int w;
};

int chooseWeight(int mode) {
  if (mode == 0) return rnd.next(1, 5);
  if (mode == 1) return 2 * rnd.next(1, 8);
  if (mode == 2) return 2 * rnd.next(1, 8) - 1;
  if (mode == 3) return rnd.any(vector<int>{1, 2, 3, 999999937, 1000000000});
  return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(0, 4);
  int n = 1;
  if (mode == 0) {
    n = rnd.next(1, 4);
  } else if (mode == 1) {
    n = rnd.next(2, 18);
  } else if (mode == 2) {
    n = rnd.next(4, 16);
  } else if (mode == 3) {
    n = rnd.next(7, 21);
  } else {
    n = rnd.next(2, 20);
  }

  int weightMode = rnd.next(0, 4);
  vector<Edge> edges;
  vector<vector<int>> tree(n + 1);

  auto addEdge = [&](int u, int v) {
    int w = chooseWeight(weightMode);
    edges.push_back({u, v, w});
    tree[u].push_back(v);
    tree[v].push_back(u);
  };

  if (mode == 0) {
    for (int i = 2; i <= n; ++i) addEdge(i - 1, i);
  } else if (mode == 1) {
    for (int i = 2; i <= n; ++i) addEdge(i - 1, i);
  } else if (mode == 2) {
    for (int i = 2; i <= n; ++i) addEdge(1, i);
  } else if (mode == 3) {
    for (int i = 2; i <= n; ++i) addEdge(i / 2, i);
  } else {
    for (int i = 2; i <= n; ++i) addEdge(rnd.next(1, i - 1), i);
  }

  int k = rnd.next(1, min(35, max(1, 2 * n)));
  vector<pair<int, int>> queries;

  queries.push_back({rnd.next(1, n), rnd.next(1, n)});
  queries.push_back({rnd.next(1, n), rnd.next(1, n)});
  int same = rnd.next(1, n);
  queries.push_back({same, same});

  if (n >= 2) {
    queries.push_back({1, n});
    queries.push_back({n, 1});
  }

  for (int i = 0; i < (int)edges.size() && (int)queries.size() < k; ++i) {
    queries.push_back({edges[i].u, edges[i].v});
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  shuffle(order.begin(), order.end());
  for (int x : order) {
    if ((int)queries.size() >= k) break;
    if (!tree[x].empty()) queries.push_back({x, rnd.any(tree[x])});
  }

  while ((int)queries.size() < k) {
    int u = rnd.next(1, n);
    int v = rnd.next(1, n);
    if (rnd.next(0, 4) == 0) v = u;
    queries.push_back({u, v});
  }

  shuffle(edges.begin(), edges.end());
  shuffle(queries.begin(), queries.end());
  queries.resize(k);

  println(n, k);
  for (const Edge& edge : edges) println(edge.u, edge.v, edge.w);
  for (const auto& query : queries) println(query.first, query.second);

  return 0;
}
