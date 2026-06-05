#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class Dsu {
  vector<int> parent;

 public:
  explicit Dsu(int n) : parent(n + 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    parent[b] = a;
    return true;
  }
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(3, 328000, "N");
  inf.readSpace();
  int s = inf.readInt(2, n - 1, "S");
  inf.readSpace();
  int p = inf.readInt(s + 1, n, "P");
  inf.readEoln();

  Dsu dsu(n);
  set<pair<int, int>> edges;
  vector<vector<int>> graph(n + 1);

  for (int i = 1; i <= n - 1; ++i) {
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readEoln();

    ensuref(a != b, "loop at edge %d: %d %d", i, a, b);
    pair<int, int> edge = minmax(a, b);
    ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, a, b);
    ensuref(dsu.unite(a, b), "cycle created by edge %d: %d %d", i, a, b);

    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  int root = dsu.find(1);
  for (int v = 2; v <= n; ++v) {
    ensuref(dsu.find(v) == root, "graph is disconnected at vertex %d", v);
  }

  vector<char> seen(n + 1, false);
  seen[p] = true;
  vector<int> stack;
  for (int start = 1; start <= n; ++start) {
    if (seen[start]) continue;

    int supports = 0;
    stack.push_back(start);
    seen[start] = true;
    while (!stack.empty()) {
      int v = stack.back();
      stack.pop_back();
      if (v <= s) ++supports;

      for (int to : graph[v]) {
        if (to == p || seen[to]) continue;
        seen[to] = true;
        stack.push_back(to);
      }
    }

    ensuref(supports <= 1,
            "component not passing through P contains %d supports, starting at vertex %d",
            supports, start);
  }

  inf.readEof();
}
