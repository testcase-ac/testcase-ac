#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

void dfs(int v) {
  vis[v] = true;
  for (int u : graph[v]) {
    if (!vis[u]) dfs(u);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int cc = 0;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) cc++, dfs(i);
  }

  int ans = cc - 1;
  m += (cc - 1);
  ans += (m - (n - 1));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
