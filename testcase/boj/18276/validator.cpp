#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class DisjointSet {
 public:
  explicit DisjointSet(int n) : parent_(n + 1), size_(n + 1, 1) {
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
    if (size_[a] < size_[b]) swap(a, b);
    parent_[b] = a;
    size_[a] += size_[b];
    return true;
  }

 private:
  vector<int> parent_;
  vector<int> size_;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(2, 100000, "n");
  inf.readEoln();

  DisjointSet dsu(n);
  set<pair<int, int>> edges;
  for (int i = 1; i <= n - 1; ++i) {
    int u = inf.readInt(1, n, "u_i");
    inf.readSpace();
    int v = inf.readInt(1, n, "v_i");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "w_i");
    inf.readEoln();

    ensuref(u != v, "loop at edge %d: %d %d", i, u, v);
    auto edge = minmax(u, v);
    ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i,
            u, v);
    ensuref(dsu.unite(u, v), "cycle introduced at edge %d: %d %d", i, u, v);
  }

  int root = dsu.find(1);
  for (int v = 2; v <= n; ++v) {
    ensuref(dsu.find(v) == root, "tree is not connected; vertex %d is separate",
            v);
  }

  inf.readEof();
}
