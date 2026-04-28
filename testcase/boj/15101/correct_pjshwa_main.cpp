#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000, BIAS = 1000;
vector<int> graph[MAX + 1];
int outdegree[MAX + 1];
bool vis[MAX + 1];

void dfs(int v) {
  vis[v] = 1;
  for (int u : graph[v]) {
    if (!vis[u]) dfs(u);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;

  while (m--) {
    int u, v;
    cin >> u >> v;

    bool f = u < 0;
    u = abs(u);

    if (f) {
      graph[u].push_back(v);
      graph[u + BIAS].push_back(v + BIAS);
      outdegree[u]++;
    }
    else graph[u].push_back(v + BIAS);
  }

  dfs(1);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (outdegree[i]) continue;

    if (vis[i] || vis[i + BIAS]) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
