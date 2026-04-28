#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj[MAXN + 1];
int vis[MAXN + 1];

void dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) {
    if (!vis[v]) dfs(v);
  }
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int cc = 0;
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    dfs(i); cc++;
  }

  cout << m - n + cc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
