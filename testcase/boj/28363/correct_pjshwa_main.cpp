#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int parent[MAXN + 1];
unordered_set<int> D[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M, Q; cin >> N >> M >> Q;
  iota(parent, parent + N + 1, 0);
  while (M--) {
    int u, v; cin >> u >> v;
    D[u].insert(v); D[v].insert(u);
  }

  while (Q--) {
    int u, v; cin >> u >> v;
    u = Find(u), v = Find(v);
    if (D[u].count(v)) {
      cout << "REFUSE\n";
      continue;
    }
    cout << "APPROVE\n";

    assert(u != v);
    if (D[u].size() < D[v].size()) swap(u, v);
    for (int x : D[v]) {
      x = Find(x);
      D[u].insert(x);
      D[x].erase(v);
      D[x].insert(u);
    }
    D[v].clear();
    Union(u, v);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
