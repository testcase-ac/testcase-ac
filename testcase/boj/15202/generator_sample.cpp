#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(0, 6);
  int n = rnd.next(1, 28);
  vector<pair<int, int>> edges;

  auto add_edge = [&](int u, int v) {
    if (rnd.next(0, 1)) {
      swap(u, v);
    }
    edges.push_back({u, v});
  };

  if (n > 1) {
    if (mode == 0) {
      for (int v = 2; v <= n; ++v) {
        add_edge(v - 1, v);
      }
    } else if (mode == 1) {
      for (int v = 2; v <= n; ++v) {
        add_edge(1, v);
      }
    } else if (mode == 2) {
      for (int v = 2; v <= n; ++v) {
        add_edge(v / 2, v);
      }
    } else {
      for (int v = 2; v <= n; ++v) {
        int parent = rnd.next(1, v - 1);
        if (mode == 4 && v > 3 && rnd.next(0, 2) == 0) {
          parent = rnd.next(max(1, v - 5), v - 1);
        }
        add_edge(parent, v);
      }
    }
  }

  vector<int> depth(n + 1, 0);
  vector<vector<int>> adj(n + 1);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> stack = {1};
  vector<int> parent(n + 1, 0);
  parent[1] = -1;
  for (int i = 0; i < static_cast<int>(stack.size()); ++i) {
    int v = stack[i];
    for (int u : adj[v]) {
      if (u == parent[v]) {
        continue;
      }
      parent[u] = v;
      depth[u] = depth[v] + 1;
      stack.push_back(u);
    }
  }

  string labels(n, 'A');
  int label_mode = rnd.next(0, 5);
  if (label_mode == 0) {
    for (int i = 0; i < n; ++i) {
      labels[i] = (i % 2 == 0 ? 'A' : 'B');
    }
  } else if (label_mode == 1) {
    for (int v = 1; v <= n; ++v) {
      labels[v - 1] = (depth[v] % 2 == 0 ? 'A' : 'B');
    }
  } else if (label_mode == 2) {
    for (int v = 1; v <= n; ++v) {
      labels[v - 1] = (depth[v] % 2 == 0 ? 'B' : 'A');
    }
  } else if (label_mode == 3) {
    char same = rnd.next(0, 1) ? 'A' : 'B';
    fill(labels.begin(), labels.end(), same);
  } else {
    int bias = rnd.next(1, 9);
    for (int i = 0; i < n; ++i) {
      labels[i] = (rnd.next(1, 10) <= bias ? 'A' : 'B');
    }
  }

  shuffle(edges.begin(), edges.end());

  println(n);
  println(labels);
  for (auto [u, v] : edges) {
    println(u, v);
  }

  return 0;
}
