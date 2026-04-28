#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int parent[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

void solve() {
  int N, M, K; cin >> N >> M >> K;

  iota(parent, parent + N + 1, 0);
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < M; ++i) {
    int u, v, w; cin >> u >> v >> w;
    edges.emplace_back(w, u, v);
  }
  sort(edges.begin(), edges.end());

  int T = N - K, uc = 0, ans = 0;
  for (auto& [w, u, v] : edges) {
    if (uc == T) break;
    if (Find(u) == Find(v)) continue;
    Union(u, v); ++uc; ans += w;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
