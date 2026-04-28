#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000, MOD = 1e9 + 7;
vector<int> adj[MAXN + 1], radj[MAXN + 1], B[MAXN + 1];
int indegree[MAXN + 1], dp[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    radj[v].push_back(u); ++indegree[u];
  }

  for (int s = 1; s <= N; ++s) {
    vector<bool> vis(N + 1, false);
    function<void(int)> dfs = [&](int u) {
      vis[u] = true;
      for (int v : adj[u]) {
        if (vis[v]) continue;
        B[s].push_back(v); dfs(v);
      }
    };
    dfs(s);
  }

  queue<int> q;
  for (int i = 1; i <= N; ++i) {
    if (!indegree[i]) q.push(i);
  }

  fill(dp + 1, dp + N + 1, 1);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : radj[u]) {
      if (--indegree[v]) continue;
      for (int x : B[v]) dp[v] = (dp[v] + dp[x]) % MOD;
      q.push(v);
    }
  }

  int ans = 0;
  for (int i = 1; i <= N; ++i) ans = (ans + dp[i]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
