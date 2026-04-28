#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, INF = 0x3f3f3f3f;
vector<pii> adj[MAXN + 1];
int deg[MAXN + 1], dp[MAXN + 1];

bool is_leaf(int v) {
  return v != 1 && deg[v] == 1;
}

void dfs(int v, int p) {
  int ret = is_leaf(v) ? INF : 0;
  for (auto& [u, w] : adj[v]) {
    if (u == p) continue;
    dfs(u, v);
    ret += min(w, dp[u]);
  }
  dp[v] = ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
    ++deg[u]; ++deg[v];
  }

  dfs(1, 0);
  cout << dp[1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
