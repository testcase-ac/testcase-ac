#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
set<int> adj[MAXN + 1];
int C[MAXN + 1], vis[MAXN + 1];

void dfs(int v) {
  vis[v] = 1;
  for (int u : adj[v]) {
    if (C[u] == C[v]) {
      cout << "-1\n";
      exit(0);
    }
    if (!vis[u]) dfs(u);
  }
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    adj[u].insert(v);
    adj[v].insert(u);
  }

  int it = 1;
  for (int i = 1; i <= n && it <= 3; ++i) {
    if (C[i]) continue;

    C[i] = it;
    for (int j = 1; j <= n; ++j) {
      if (C[j] || adj[i].count(j)) continue;
      C[j] = it;
    }
    ++it;
  }

  if (it <= 3) {
    cout << "-1\n";
    return;
  }

  ll T[4]{};
  for (int i = 1; i <= n; ++i) ++T[C[i]];

  ll tot = T[1] * (T[2] + T[3]) + T[2] * T[3];
  if (tot != m) {
    cout << "-1\n";
    return;
  }

  for (int i = 1; i <= n; ++i) {
    if (C[i]) {
      int U[4]{}; U[C[i]] = T[C[i]];
      for (int j : adj[i]) ++U[C[j]];
      for (int c = 1; c <= 3; ++c) if (!U[c]) return cout << "-1\n", void();
    }
    else return cout << "-1\n", void();
  }
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) dfs(i);
  }

  for (int i = 1; i <= n; ++i) cout << C[i] << ' '; cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
