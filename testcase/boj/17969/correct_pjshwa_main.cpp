#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<pii> graph[MAX + 1];
bool vis[MAX + 1];
ll sz[MAX + 1], dis[MAX + 1], dp[MAX + 1];

inline void dfs(int v) {
  vis[v] = 1;
  sz[v] = dis[v] = dp[v] = 0;

	for (auto& [d, w] : graph[v]) {
    if (vis[d]) continue;
    dfs(d);

    dp[v] += 2 * sz[v] * sz[d] + dis[v] * sz[d] + dis[d] * sz[v] + dp[d];
    sz[v] += sz[d];
    dis[v] += dis[d];
  }
  dis[v] += sz[v];
  sz[v] += 1;
  dp[v] += dis[v];
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }
  dfs(0);
  cout << 2 * dp[0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
