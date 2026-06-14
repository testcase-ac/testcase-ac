#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
 public:
  explicit Dsu(int n) : parent_(n + 1), size_(n + 1, 1) {
    iota(parent_.begin(), parent_.end(), 0);
  }

  int Find(int x) {
    if (parent_[x] == x) return x;
    return parent_[x] = Find(parent_[x]);
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

  int n = inf.readInt(3, 200000, "N");
  inf.readSpace();
  int m = inf.readInt(3, 200000, "M");
  inf.readSpace();
  inf.readLong(1LL, 1000000000LL, "K");
  inf.readEoln();

  Dsu dsu(n);
  set<pair<int, int>> edges;
  for (int i = 1; i <= m; ++i) {
    int a = inf.readInt(1, n, "a_i");
    inf.readSpace();
    int b = inf.readInt(1, n, "b_i");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "c_i");
    inf.readEoln();

    ensuref(a != b, "loop at edge %d: %d %d", i, a, b);
    ensuref(edges.insert(minmax(a, b)).second,
            "multiple edge at edge %d: %d %d", i, a, b);
    dsu.Unite(a, b);
  }

  int root = dsu.Find(1);
  for (int v = 2; v <= n; ++v) {
    ensuref(dsu.Find(v) == root, "graph is disconnected: vertex %d", v);
  }

  int x = inf.readInt(1, n, "X");
  inf.readEoln();

  vector<int> seen(n + 1, 0);
  for (int i = 1; i <= x; ++i) {
    if (i > 1) inf.readSpace();
    int e = inf.readInt(1, n, "E_i");
    ensuref(!seen[e], "duplicate exit at position %d: %d", i, e);
    seen[e] = 1;
  }
  inf.readEoln();
  inf.readEof();
}
