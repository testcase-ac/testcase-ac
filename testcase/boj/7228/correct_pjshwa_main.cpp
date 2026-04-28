#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<pii> adj[MAXN][2];
int vis[MAXN][2];

void dfs(int v, int c) {
  vis[v][c] = 1;
  for (auto [u, w] : adj[v][c]) {
    if (!vis[u][w]) dfs(u, w);
  }
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    int u, v, w; cin >> u >> v >> w; --u, --v;
    for (int j = 0; j < 2; ++j) {
      adj[u][j].emplace_back(v, j ^ w);
      adj[v][j].emplace_back(u, j ^ w);
    }
  }
  for (int i = 0; i < N; ++i) {
    if (vis[i][0] || vis[i][1]) continue;
    dfs(i, 0);
    if (vis[i][1]) return cout << "NEEGZISTUOJA\n", void();
  }
  cout << "EGZISTUOJA\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
