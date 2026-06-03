#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
  vector<int> parent;

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

  int n = inf.readInt(2, 200000, "N");
  inf.readSpace();
  int m = inf.readInt(1, n - 1, "M");
  inf.readEoln();

  Dsu dsu(n);
  set<pair<int, int>> edges;
  for (int i = 1; i <= m; ++i) {
    int u = inf.readInt(1, n, "u");
    inf.readSpace();
    int v = inf.readInt(1, n, "v");
    inf.readEoln();

    ensuref(u != v, "self-loop at edge %d: %d", i, u);
    auto edge = minmax(u, v);
    ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, u,
            v);
    ensuref(dsu.unite(u, v), "cycle introduced at edge %d: %d %d", i, u, v);
  }

  inf.readEof();
}
