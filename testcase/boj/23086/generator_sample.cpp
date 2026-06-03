#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int n = rnd.next(2, 14);
  int mode = rnd.next(4);

  vector<pair<int, int>> edges;
  set<pair<int, int>> used;

  auto addEdge = [&](int u, int v) {
    if (u > v) swap(u, v);
    if (u == v || used.count({u, v})) return false;
    used.insert({u, v});
    edges.push_back({u, v});
    return true;
  };

  if (mode == 0) {
    for (int v = 2; v <= n; ++v) addEdge(v - 1, v);
  } else if (mode == 1) {
    for (int v = 2; v <= n; ++v) addEdge(1, v);
  } else {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());
    for (int i = 1; i < n; ++i) addEdge(order[i], order[rnd.next(i)]);
  }

  vector<pair<int, int>> candidates;
  for (int u = 1; u <= n; ++u) {
    for (int v = u + 1; v <= n; ++v) {
      if (!used.count({u, v})) candidates.push_back({u, v});
    }
  }
  shuffle(candidates.begin(), candidates.end());

  int maxExtra = (int)candidates.size();
  int extra = 0;
  if (maxExtra > 0) {
    if (mode == 3) {
      extra = rnd.next(maxExtra / 2, maxExtra);
    } else {
      extra = rnd.next(0, min(maxExtra, n + rnd.next(0, n)));
    }
  }

  vector<int> removablePositions;
  for (int i = 0; i < extra; ++i) {
    edges.push_back(candidates[i]);
    removablePositions.push_back((int)edges.size());
  }

  vector<int> perm(n + 1);
  iota(perm.begin(), perm.end(), 0);
  shuffle(perm.begin() + 1, perm.end());
  for (auto& edge : edges) {
    edge = {perm[edge.first], perm[edge.second]};
    if (rnd.next(2)) swap(edge.first, edge.second);
  }

  vector<int> edgeOrder(edges.size());
  iota(edgeOrder.begin(), edgeOrder.end(), 0);
  shuffle(edgeOrder.begin(), edgeOrder.end());

  vector<pair<int, int>> shuffledEdges;
  vector<int> oldToNew(edges.size() + 1);
  for (int i = 0; i < (int)edgeOrder.size(); ++i) {
    int oldIndex = edgeOrder[i];
    shuffledEdges.push_back(edges[oldIndex]);
    oldToNew[oldIndex + 1] = i + 1;
  }

  int k = removablePositions.empty() ? 0 : rnd.next(0, (int)removablePositions.size());
  shuffle(removablePositions.begin(), removablePositions.end());

  vector<int> removals;
  for (int i = 0; i < k; ++i) removals.push_back(oldToNew[removablePositions[i]]);
  shuffle(removals.begin(), removals.end());

  println(n, (int)shuffledEdges.size(), k);
  for (auto [u, v] : shuffledEdges) println(u, v);
  for (int index : removals) println(index);

  return 0;
}
