#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<pii> graph[MAX + 1];
bool vis[MAX + 1], ban[MAX + 1];

pii maxd(int node, int cd) {
  vis[node] = true;

  int mv = node, md = cd;
  for (pii dst : graph[node]) {
    auto [v, d] = dst;
    if (ban[v]) continue;

    if (!vis[v]) {
      auto [dv, dd] = maxd(v, cd + d);
      if (md < dd) md = dd, mv = dv;
    }
  }

  return {mv, md};
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  memset(vis, 0, sizeof(vis));
  int v1 = maxd(1, 0).first;
  memset(vis, 0, sizeof(vis));
  int v2 = maxd(v1, 0).first;

  ban[v2] = 1;
  memset(vis, 0, sizeof(vis));
  int d1 = maxd(v1, 0).second;
  ban[v2] = 0, ban[v1] = 1;
  memset(vis, 0, sizeof(vis));
  int d2 = maxd(v2, 0).second;

  cout << max(d1, d2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
