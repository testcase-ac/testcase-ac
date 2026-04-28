#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

pii maxd(int node, int cd) {
  vis[node] = true;

  int mv = node, md = cd;
  for (int v : graph[node]) {
    if (!vis[v]) {
      auto [dv, dd] = maxd(v, cd + 1);
      if (md < dd) md = dd, mv = dv;
    }
  }

  return {mv, md};
}

void dfs(int v) {
  vis[v] = 1;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  vector<int> ss;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      ss.push_back(i);
      dfs(i);
    }
  }

  memset(vis, 0, sizeof vis);

  vector<int> es;
  for (int s : ss) es.push_back(maxd(s, 0).first);

  memset(vis, 0, sizeof vis);

  vector<int> ds;
  for (int e : es) ds.push_back(maxd(e, 0).second);

  int ans = accumulate(ds.begin(), ds.end(), 0);
  ans += ds.size();
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
