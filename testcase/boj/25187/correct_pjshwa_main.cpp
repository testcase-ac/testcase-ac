#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int val[MAX + 1];
bool vis1[MAX + 1], vis2[MAX + 1], able[MAX + 1];
vector<int> graph[MAX + 1];
int cur, tot;

void dfs1(int v) {
  vis1[v] = 1;
  cur += val[v], tot++;

  for (int d : graph[v]) {
    if (!vis1[d]) dfs1(d);
  }
}

void dfs2(int v, bool m) {
  vis2[v] = 1;
  able[v] = m;

  for (int d : graph[v]) {
    if (!vis2[d]) dfs2(d, m);
  }
}

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) cin >> val[i];
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) {
    if (vis1[i]) continue;
    cur = tot = 0;
    dfs1(i);
    dfs2(i, 2 * cur > tot);
  }

  while (q--) {
    int x;
    cin >> x;
    cout << able[x] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
