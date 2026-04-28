#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1], st[MAX + 1], is_cycle[MAX + 1];

bool dfs(int v) {
  if (!vis[v]) {
    vis[v] = st[v] = 1;
    for (int d : graph[v]) {
      if (!vis[d] && dfs(d)) {
        is_cycle[v] = 1;
        return 1;
      }
      else if (st[d]) {
        is_cycle[v] = 1;
        return 1;
      }
    }
  }

  st[v] = 0;
  return 0;
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      if (dfs(i)) is_cycle[i] = 1;
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!is_cycle[i]) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
