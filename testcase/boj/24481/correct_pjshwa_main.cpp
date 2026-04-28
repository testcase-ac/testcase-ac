#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
set<int> graph[MAX + 1];
int depth[MAX + 1];
bool vis[MAX + 1];

void dfs(int v, int dpt) {
  vis[v] = 1;
  depth[v] = dpt;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d, dpt + 1);
  }
}

void solve() {
  int n, m, r;
  cin >> n >> m >> r;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].insert(v);
    graph[v].insert(u);
  }

  memset(depth, -1, sizeof(depth));
  dfs(r, 0);
  for (int i = 1; i <= n; i++) cout << depth[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
