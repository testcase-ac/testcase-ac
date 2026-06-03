#include "testlib.h"

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

  int n = inf.readInt(2, 100000, "n");
  inf.readSpace();
  int max_m = min(1LL * n * (n - 1) / 2, 200000LL);
  int m = inf.readInt(n - 1, max_m, "m");
  inf.readSpace();
  int k = inf.readInt(0, m - n + 1, "k");
  inf.readEoln();

  vector<pair<int, int>> edges(m + 1);
  set<pair<int, int>> seen_edges;
  for (int i = 1; i <= m; ++i) {
    int u = inf.readInt(1, n, "u_i");
    inf.readSpace();
    int v = inf.readInt(1, n, "v_i");
    inf.readEoln();

    ensuref(u != v, "self-loop at edge %d: %d %d", i, u, v);
    pair<int, int> edge = minmax(u, v);
    ensuref(seen_edges.insert(edge).second, "duplicate edge at index %d: %d %d", i, u, v);
    edges[i] = edge;
  }

  vector<bool> removed(m + 1, false);
  for (int i = 1; i <= k; ++i) {
    int r = inf.readInt(1, m, "R_i");
    inf.readEoln();
    ensuref(!removed[r], "duplicate removal index at list position %d: %d", i, r);
    removed[r] = true;
  }

  Dsu dsu(n);
  for (int i = 1; i <= m; ++i) {
    if (removed[i]) continue;
    dsu.Unite(edges[i].first, edges[i].second);
  }
  int root = dsu.Find(1);
  for (int v = 2; v <= n; ++v) {
    ensuref(dsu.Find(v) == root, "graph is disconnected after listed removals; vertex %d is separated", v);
  }

  inf.readEof();
}
