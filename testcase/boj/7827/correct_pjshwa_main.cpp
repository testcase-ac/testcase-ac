#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 2500;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void dfs(int v) {
  vis[v] = true;
  for (int u : graph[v]) {
    if (!vis[u]) dfs(u);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) graph[i].clear();

  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    memset(vis, 0, sizeof(vis));
    dfs(i);
    for (int j = 1; j <= n; j++) if (vis[j] && i != j) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
