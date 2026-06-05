#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int n = rnd.next(3, 40);
  int s = rnd.next(2, min(8, n - 1));
  int p = rnd.next(s + 1, n);

  vector<vector<int>> components;
  for (int support = 1; support <= s; ++support) {
    components.push_back({support});
  }

  vector<int> normal;
  for (int v = s + 1; v <= n; ++v) {
    if (v != p) normal.push_back(v);
  }
  shuffle(normal.begin(), normal.end());

  int zeroSupportComponents = normal.empty() ? 0 : rnd.next(0, min(4, (int)normal.size()));
  for (int i = 0; i < zeroSupportComponents; ++i) {
    components.push_back({});
  }

  for (int v : normal) {
    int idx;
    if (rnd.next(100) < 30 && (int)components.size() < n - 1) {
      components.push_back({});
      idx = (int)components.size() - 1;
    } else {
      idx = rnd.next((int)components.size());
    }
    components[idx].push_back(v);
  }

  vector<pair<int, int>> edges;
  int shape = rnd.next(4);
  for (auto component : components) {
    if (component.empty()) continue;

    shuffle(component.begin(), component.end());
    edges.push_back({p, component[0]});

    if (shape == 0) {
      for (int i = 1; i < (int)component.size(); ++i) {
        edges.push_back({component[i - 1], component[i]});
      }
    } else if (shape == 1) {
      for (int i = 1; i < (int)component.size(); ++i) {
        edges.push_back({component[0], component[i]});
      }
    } else {
      for (int i = 1; i < (int)component.size(); ++i) {
        int parentLimit = shape == 2 ? i : min(i, 3);
        edges.push_back({component[rnd.next(parentLimit)], component[i]});
      }
    }
  }

  shuffle(edges.begin(), edges.end());
  for (auto& edge : edges) {
    if (rnd.next(2)) swap(edge.first, edge.second);
  }

  println(n, s, p);
  for (auto [a, b] : edges) {
    println(a, b);
  }

  return 0;
}
