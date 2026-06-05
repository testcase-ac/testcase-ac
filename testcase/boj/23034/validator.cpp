#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class Dsu {
 public:
  explicit Dsu(int n) : parent_(n + 1), size_(n + 1, 1) {
    iota(parent_.begin(), parent_.end(), 0);
  }

  int Find(int x) {
    if (parent_[x] == x) return x;
    parent_[x] = Find(parent_[x]);
    return parent_[x];
  }

  void Unite(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return;
    if (size_[a] < size_[b]) swap(a, b);
    parent_[b] = a;
    size_[a] += size_[b];
  }

 private:
  vector<int> parent_;
  vector<int> size_;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(2, 1000, "N");
  inf.readSpace();
  int m = inf.readInt(1, 100000, "M");
  inf.readEoln();

  ensuref(m >= n, "M must be at least N: N=%d, M=%d", n, m);
  int maxSimpleEdges = n * (n - 1) / 2;
  ensuref(m <= maxSimpleEdges,
          "M exceeds the number of simple undirected edges: N=%d, M=%d", n, m);

  Dsu dsu(n);
  set<pair<int, int>> edges;
  for (int i = 1; i <= m; ++i) {
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readSpace();
    inf.readInt(1, 100000, "C");
    inf.readEoln();

    ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);
    auto edge = minmax(a, b);
    ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, a, b);
    dsu.Unite(a, b);
  }

  int root = dsu.Find(1);
  for (int v = 2; v <= n; ++v) {
    ensuref(dsu.Find(v) == root, "graph is disconnected: vertex %d is unreachable from 1", v);
  }

  int q = inf.readInt(1, 10000, "Q");
  inf.readEoln();
  for (int i = 1; i <= q; ++i) {
    int x = inf.readInt(1, n, "X");
    inf.readSpace();
    int y = inf.readInt(1, n, "Y");
    inf.readEoln();

    ensuref(x != y, "query %d has equal leaders: %d", i, x);
  }

  inf.readEof();
}
