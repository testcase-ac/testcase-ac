#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MOD = 1e9 + 7;
vector<int> adj[MAXN + 1], C;
int vis[MAXN + 1];

void dfs(int v) {
  vis[v] = 1; C.push_back(v);
  for (int u : adj[v]) {
    if (!vis[u]) dfs(u);
  }
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  ll ans = 1;
  for (int i = 1; i <= N; ++i) {
    if (vis[i] || adj[i].empty()) continue;

    C.clear();
    dfs(i);

    int ec = 0, V = C.size();
    for (int v : C) ec += adj[v].size();
    ec /= 2;

    if (ec == V - 1) ans = (ans * V) % MOD;
    else if (ec == V) ans = (ans * 2) % MOD;
    else ans = 0;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
