#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
set<int> graph[MAX + 1];
int order[MAX + 1];
bool vis[MAX + 1];
int o;

void dfs(int v) {
  vis[v] = 1;
  order[v] = ++o;
  for (int d : graph[v]) {
    d = -d;
    if (!vis[d]) dfs(d);
  }
}

void solve() {
  int n, m, r;
  cin >> n >> m >> r;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].insert(-v);
    graph[v].insert(-u);
  }

  dfs(r);
  for (int i = 1; i <= n; i++) cout << order[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
