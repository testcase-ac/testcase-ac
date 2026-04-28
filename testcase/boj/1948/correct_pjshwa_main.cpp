#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
vector<pii> adj[MAXN + 1];
int S, vis[MAXN + 1], dp[MAXN + 1];

int rec(int u) {
  if (dp[u] != -1) return dp[u];
  if (u == S) return dp[u] = 0;

  int ret = 0;
  for (auto& [v, w] : adj[u]) {
    ret = max(ret, rec(v) + w);
  }
  return dp[u] = ret;
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[v].emplace_back(u, w);
  }
  int T; cin >> S >> T;

  memset(dp, -1, sizeof(dp));
  cout << rec(T) << '\n';

  int ans = 0;
  queue<int> Q; Q.push(T);
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    for (auto& [v, w] : adj[u]) {
      if (dp[u] != dp[v] + w) continue;
      ++ans;
      if (!vis[v]) vis[v] = 1, Q.push(v);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
