#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
 public:
  explicit Dsu(int n) : parent_(n + 1), rank_(n + 1, 0) {
    iota(parent_.begin(), parent_.end(), 0);
  }

  int find(int x) {
    if (parent_[x] == x) return x;
    return parent_[x] = find(parent_[x]);
  }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (rank_[a] < rank_[b]) swap(a, b);
    parent_[b] = a;
    if (rank_[a] == rank_[b]) ++rank_[a];
  }

 private:
  vector<int> parent_;
  vector<int> rank_;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(2, 1000, "n");
  inf.readEoln();

  int m = inf.readInt(1, 5000, "m");
  inf.readEoln();

  Dsu dsu(n);
  vector<vector<int>> enemies_of(n + 1);
  vector<pair<int, int>> enemy_pairs;

  for (int i = 0; i < m; ++i) {
    char relation = inf.readToken("F|E", "relation")[0];
    inf.readSpace();
    int p = inf.readInt(1, n, "p");
    inf.readSpace();
    int q = inf.readInt(1, n, "q");
    inf.readEoln();

    ensuref(p < q, "expected p < q at fact %d, got %d %d", i + 1, p, q);

    if (relation == 'F') {
      dsu.unite(p, q);
    } else {
      enemy_pairs.push_back({p, q});
      enemies_of[p].push_back(q);
      enemies_of[q].push_back(p);
    }
  }

  for (int student = 1; student <= n; ++student) {
    const vector<int>& enemies = enemies_of[student];
    for (int i = 1; i < static_cast<int>(enemies.size()); ++i) {
      dsu.unite(enemies[0], enemies[i]);
    }
  }

  for (pair<int, int> enemy_pair : enemy_pairs) {
    ensuref(dsu.find(enemy_pair.first) != dsu.find(enemy_pair.second),
            "known enemy pair %d %d is also implied to be friends",
            enemy_pair.first, enemy_pair.second);
  }

  inf.readEof();
}
