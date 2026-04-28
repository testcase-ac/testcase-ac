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

void bfs(int s) {
  memset(vis, 0, sizeof(vis));
  queue<int> q;
  q.push(s);
  vis[s] = true;

  int it = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    order[v] = ++it;
    for (int d : graph[v]) {
      d = -d;
      if (!vis[d]) vis[d] = true, q.push(d);
    }
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

  bfs(r);
  for (int i = 1; i <= n; i++) cout << order[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
