#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
vector<pll> graph[MAX + 1];
bool vis[MAX + 1];

pll maxd(int node, ll cd) {
  vis[node] = true;

  ll mv = node, md = cd;
  for (pll dst : graph[node]) {
    auto [v, d] = dst;
    if (!vis[v]) {
      auto [dv, dd] = maxd(v, cd + d);
      if (md < dd) md = dd, mv = dv;
    }
  }

  return {mv, md};
}

void solve() {
  int n, k;
  cin >> n >> k;

  ll sum = 0;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
    sum += w;
  }

  if (k >= 2) return cout << sum << '\n', void();

  memset(vis, 0, sizeof(vis));
  int v1 = maxd(1, 0).first;
  memset(vis, 0, sizeof(vis));
  cout << maxd(v1, 0).second << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
