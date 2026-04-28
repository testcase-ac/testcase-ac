#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<pii> graph[MAX + 1];
int vis[MAX + 1], leaf;
set<int> uedges[MAX + 1];

void dfs(int v, int cc) {
  vis[v] = cc;
  int cnt = 0;
  for (pii& d : graph[v]) {
    if (!vis[d.first]) {
      cnt++;
      uedges[cc].insert(d.second);
      dfs(d.first, cc);
    }
  }
  if (cnt == 0) leaf = v;
}

void solve() {
  int n, m;
  cin >> n >> m;
  if (m == 0) return cout << "-1\n", void();

  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back({b, i});
    graph[b].push_back({a, i});
  }

  int cc = 0;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i, ++cc);
  }

  set<int> uv1, uv2;
  if (cc == 1) {
    uv2.insert(leaf);
    for (pii& p : graph[leaf]) uedges[1].erase(p.second);
    for (int j = 1; j <= n; j++) {
      if (j != leaf) uv1.insert(j);
    }
  }
  if (cc == 2) {
    for (int i = 1; i <= n; i++) {
      if (vis[i] == 1) uv1.insert(i);
      if (vis[i] == 2) uv2.insert(i);
    }
  }

  if (uv1.size() == uv2.size()) return cout << "-1\n", void();

  cout << uv1.size() << ' ' << uv2.size() << '\n';
  for (int v : uv1) cout << v << ' ';
  cout << '\n';
  for (int e : uedges[1]) cout << e << ' ';
  cout << '\n';
  for (int v : uv2) cout << v << ' ';
  cout << '\n';
  for (int e : uedges[2]) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
