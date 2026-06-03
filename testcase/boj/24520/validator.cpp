#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

class DisjointSet {
 public:
  explicit DisjointSet(int n) : parent_(n + 1), rank_(n + 1, 0) {
    iota(parent_.begin(), parent_.end(), 0);
  }

  int find(int x) {
    if (parent_[x] == x) return x;
    return parent_[x] = find(parent_[x]);
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (rank_[a] < rank_[b]) swap(a, b);
    parent_[b] = a;
    if (rank_[a] == rank_[b]) ++rank_[a];
    return true;
  }

 private:
  vector<int> parent_;
  vector<int> rank_;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, 100000, "N");
  inf.readSpace();
  int k = inf.readInt(1, 100000, "K");
  inf.readEoln();

  DisjointSet dsu(n);
  int components = n;

  for (int i = 1; i <= n - 1; ++i) {
    int u = inf.readInt(1, n, "edge_u");
    inf.readSpace();
    int v = inf.readInt(1, n, "edge_v");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "edge_w");
    inf.readEoln();

    ensuref(u != v, "edge %d has the same endpoint %d", i, u);
    ensuref(dsu.unite(u, v), "edge %d creates a cycle between %d and %d", i, u, v);
    --components;
  }

  ensuref(components == 1, "roads do not connect all villages");

  for (int i = 1; i <= k; ++i) {
    inf.readInt(1, n, "query_u");
    inf.readSpace();
    inf.readInt(1, n, "query_v");
    inf.readEoln();
  }

  inf.readEof();
}
