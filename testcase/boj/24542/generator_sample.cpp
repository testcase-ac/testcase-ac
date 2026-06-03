#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<int> shuffledLabels(int n) {
  vector<int> label(n + 1);
  iota(label.begin(), label.end(), 0);
  shuffle(label.begin() + 1, label.end());
  return label;
}

void addPath(vector<pair<int, int>>& edges, const vector<int>& nodes) {
  for (int i = 1; i < int(nodes.size()); ++i) {
    edges.push_back({nodes[i - 1], nodes[i]});
  }
}

void addStar(vector<pair<int, int>>& edges, const vector<int>& nodes) {
  for (int i = 1; i < int(nodes.size()); ++i) {
    edges.push_back({nodes[0], nodes[i]});
  }
}

void addRandomTree(vector<pair<int, int>>& edges, const vector<int>& nodes) {
  for (int i = 1; i < int(nodes.size()); ++i) {
    edges.push_back({nodes[i], nodes[rnd.next(i)]});
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(6);
  int n;
  if (mode == 0) {
    n = rnd.next(2, 8);
  } else if (mode == 1) {
    n = rnd.next(3, 14);
  } else {
    n = rnd.next(6, 18);
  }

  vector<int> label = shuffledLabels(n);
  vector<pair<int, int>> edges;

  if (mode == 0) {
    int u = rnd.next(1, n);
    int v = rnd.next(1, n - 1);
    if (v >= u) ++v;
    edges.push_back({label[u], label[v]});
  } else if (mode == 1) {
    vector<int> nodes;
    for (int i = 1; i <= n; ++i) nodes.push_back(label[i]);
    addPath(edges, nodes);
  } else if (mode == 2) {
    vector<int> nodes;
    for (int i = 1; i <= n; ++i) nodes.push_back(label[i]);
    addStar(edges, nodes);
  } else if (mode == 3) {
    int firstSize = rnd.next(2, n - 2);
    vector<int> first, second;
    for (int i = 1; i <= firstSize; ++i) first.push_back(label[i]);
    for (int i = firstSize + 1; i <= n; ++i) second.push_back(label[i]);
    addPath(edges, first);
    addStar(edges, second);
  } else if (mode == 4) {
    int used = 1;
    while (used <= n) {
      int remaining = n - used + 1;
      int size = rnd.next(1, min(remaining, 6));
      vector<int> nodes;
      for (int i = 0; i < size; ++i) nodes.push_back(label[used + i]);
      if (size >= 2) {
        if (rnd.next(2) == 0) {
          addPath(edges, nodes);
        } else {
          addRandomTree(edges, nodes);
        }
      }
      used += size;
    }
  } else {
    int m = rnd.next(1, n - 1);
    for (int i = 2; i <= m + 1; ++i) {
      edges.push_back({label[i], label[rnd.next(1, i - 1)]});
    }
  }

  shuffle(edges.begin(), edges.end());
  for (auto& edge : edges) {
    if (rnd.next(2) == 0) swap(edge.first, edge.second);
  }

  println(n, int(edges.size()));
  for (const auto& edge : edges) {
    println(edge.first, edge.second);
  }

  return 0;
}
