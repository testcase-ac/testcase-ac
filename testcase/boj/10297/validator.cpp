#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
 public:
  explicit Dsu(int n) : parent_(n + 1), rank_(n + 1, 0) {
    iota(parent_.begin(), parent_.end(), 0);
  }

  int Find(int x) {
    if (parent_[x] == x) return x;
    return parent_[x] = Find(parent_[x]);
  }

  bool Unite(int a, int b) {
    int root_a = Find(a);
    int root_b = Find(b);
    if (root_a == root_b) return false;
    if (rank_[root_a] < rank_[root_b]) swap(root_a, root_b);
    parent_[root_b] = root_a;
    if (rank_[root_a] == rank_[root_b]) ++rank_[root_a];
    return true;
  }

 private:
  vector<int> parent_;
  vector<int> rank_;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int t = inf.readInt(1, 10, "T");
  inf.readEoln();

  for (int tc = 1; tc <= t; ++tc) {
    setTestCase(tc);

    // CHECK: The statement only gives N <= 100000; islands numbered 1..N and
    // tree structure require at least one island.
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
      int a = inf.readInt(1, n, "a");
      inf.readSpace();
      int b = inf.readInt(1, n, "b");
      inf.readEoln();

      ensuref(a < b, "edge %d must satisfy a < b, got %d %d", i, a, b);
      ensuref(edges.insert({a, b}).second,
              "duplicate edge %d: %d %d", i, a, b);
      ensuref(dsu.Unite(a, b), "edge %d creates a cycle: %d %d", i, a, b);
    }

    for (int i = 1; i <= n; ++i) {
      if (i > 1) inf.readSpace();
      inf.readInt(-9999, 9999, "X_i");
    }
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
      if (i > 1) inf.readSpace();
      inf.readInt(0, 1, "safe_i");
    }
    inf.readEoln();

    int root = dsu.Find(1);
    for (int i = 2; i <= n; ++i) {
      ensuref(dsu.Find(i) == root, "tree is disconnected at vertex %d", i);
    }
  }

  inf.readEof();
}
