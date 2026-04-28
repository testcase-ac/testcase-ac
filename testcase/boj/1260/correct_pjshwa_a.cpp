#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool vis[1000];
vector<int> g[1000];

void dfs(int v) {
  vis[v] = true;
  cout << v + 1 << ' ';
  for (int d : g[v]) {
    if (!vis[d]) dfs(d);
  }
}

void bfs(int v) {
  queue<int> q;
  q.push(v);

  while (!q.empty()) {
    int cv = q.front();
    q.pop();

    if (vis[cv]) continue;
    vis[cv] = true;
    cout << cv + 1 << ' ';

    for (int d : g[cv]) {
      if (!vis[d]) q.push(d);
    }
  }
}

int main() {
  fast_io();

  int n, m, v, a, b;
  cin >> n >> m >> v;

  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    g[a - 1].push_back(b - 1);
    g[b - 1].push_back(a - 1);
  }

  for (int i = 0; i < n; i++) sort(g[i].begin(), g[i].end());

  dfs(v - 1);
  cout << '\n';
  memset(vis, 0, sizeof(vis));
  bfs(v - 1);
}
