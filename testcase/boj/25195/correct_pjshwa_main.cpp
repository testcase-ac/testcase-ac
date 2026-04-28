#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1], ban[MAX + 1], terminal[MAX + 1];
int outdegree[MAX + 1];

void dfs(int v) {
  vis[v] = 1;
  for (int u : graph[v]) {
    if (!vis[u] && !ban[u]) dfs(u);
  }
}

void solve() {
  int n, m, b;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    outdegree[u]++;
  }
  cin >> b;
  for (int i = 0; i < b; i++) {
    int x;
    cin >> x;
    ban[x] = true;
  }
  for (int i = 1; i <= n; i++) {
    if (outdegree[i] == 0) terminal[i] = true;
  }

  if (!ban[1]) dfs(1);
  for (int i = 1; i <= n; i++) {
    if (vis[i] && terminal[i]) return cout << "yes\n", void();
  }

  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
