#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 750;
int X[MAXN + 1], Y[MAXN + 1];
int parent[MAXN + 1];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> X[i] >> Y[i];

  iota(parent, parent + N + 1, 0);
  int M; cin >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    Union(u, v);
  }

  vector<tuple<int, int, int>> edges;
  for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) {
    int dx = X[i] - X[j], dy = Y[i] - Y[j];
    edges.emplace_back(dx * dx + dy * dy, i, j);
  }
  sort(edges.begin(), edges.end());

  for (auto& [_, u, v] : edges) {
    if (Find(u) != Find(v)) {
      cout << u << ' ' << v << '\n';
      Union(u, v);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
