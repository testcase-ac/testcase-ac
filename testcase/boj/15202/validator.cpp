#include "testlib.h"

#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class DisjointSet {
 public:
  explicit DisjointSet(int n) : parent_(n), rank_(n, 0) {
    iota(parent_.begin(), parent_.end(), 0);
  }

  int Find(int v) {
    if (parent_[v] == v) {
      return v;
    }
    parent_[v] = Find(parent_[v]);
    return parent_[v];
  }

  bool Unite(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) {
      return false;
    }
    if (rank_[a] < rank_[b]) {
      swap(a, b);
    }
    parent_[b] = a;
    if (rank_[a] == rank_[b]) {
      ++rank_[a];
    }
    return true;
  }

 private:
  vector<int> parent_;
  vector<int> rank_;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, 300000, "n");
  inf.readEoln();

  string labels = inf.readToken("[AB]{1,300000}", "labels");
  ensuref(static_cast<int>(labels.size()) == n,
          "labels length must be n: got %d, expected %d",
          static_cast<int>(labels.size()), n);
  inf.readEoln();

  DisjointSet dsu(n);
  set<pair<int, int>> edges;
  for (int i = 1; i <= n - 1; ++i) {
    int x = inf.readInt(1, n, "x");
    inf.readSpace();
    int y = inf.readInt(1, n, "y");
    inf.readEoln();

    ensuref(x != y, "edge %d is a loop: %d %d", i, x, y);
    pair<int, int> edge = minmax(x, y);
    ensuref(edges.insert(edge).second, "edge %d is duplicated: %d %d", i, x, y);
    dsu.Unite(x - 1, y - 1);
  }

  int root = dsu.Find(0);
  for (int v = 1; v < n; ++v) {
    ensuref(dsu.Find(v) == root, "vertices 1 and %d are disconnected", v + 1);
  }

  inf.readEof();
}
