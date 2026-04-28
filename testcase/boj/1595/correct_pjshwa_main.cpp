#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<pii> graph[MAX + 1];
bool vis[MAX + 1];

pii maxd(int node, int cd) {
  vis[node] = true;

  int mv = node, md = cd, dv, dd;
  for (auto [v, d] : graph[node]) {
    if (!vis[v]) {
      auto [dv, dd] = maxd(v, cd + d);
      if (md < dd) {
        md = dd;
        mv = dv;
      }
    }
  }

  return {mv, md};
}

void solve() {
  int a, b, c;
  int n = 1;
  while (cin >> a >> b >> c) {
    n++;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }

  auto [mv, md] = maxd(1, 0);
  memset(vis, 0, sizeof(vis));
  tie(mv, md) = maxd(mv, 0);
  cout << md << '\n';
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
