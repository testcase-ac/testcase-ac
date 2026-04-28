#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN + 1], radj[MAXN + 1], R;
int indegree[MAXN + 1], E[MAXN + 1], vis[MAXN + 1];
__int128_t dp[MAXN + 1];

void dfs(int v) {
  R.push_back(v); vis[v] = 1;
  for (int u : radj[v]) {
    if (!vis[u]) dfs(u);
  }
}

void solve() {
  int N, M; cin >> N >> M;

  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); radj[v].push_back(u);
    ++indegree[v];
  }

  fill(dp, dp + N + 1, 0); dp[1] = 1;
  queue<int> Q; Q.push(1);
  while (!Q.empty()) {
    int v = Q.front(); Q.pop();

    fill(vis, vis + N + 1, 0); R.clear();
    dfs(v);

    for (int u : R) {
      if (u != v) dp[v] -= dp[u];
    }

    for (int u : adj[v]) {
      if (--indegree[u] == 0) Q.push(u);
    }
  }

  cout << (ll)dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
