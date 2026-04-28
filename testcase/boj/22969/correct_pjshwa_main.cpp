#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1], g2n[MAX + 1];
bool vis[MAX + 1], edge[MAX + 1];
int indegree[MAX + 1];
int parent[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void dfs(int v) {
  vis[v] = 1;
  for (int d : graph[v]) {
    if (!vis[d]) Union(v, d), dfs(d);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
    indegree[u]++;
    indegree[v]++;
  }

  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }
  for (int i = 1; i <= n; i++) g2n[Find(i)].push_back(i);

  for (int i = 1; i <= n; i++) {
    auto& vv = g2n[i];
    if (vv.empty()) continue;

    for (int v : vv) {
      if (indegree[v] >= 3) {
        if (indegree[v] > 4) return cout << "NIE\n", void();

        vector<pair<int, int>> d;
        for (int j : graph[v]) d.push_back({indegree[j], j});
        sort(d.begin(), d.end());
        if (d[0].first == 1 && d[1].first == 1) edge[d[0].second] = edge[d[1].second] = 1;
        else return cout << "NIE\n", void();
      }
    }

    int oc = 0, uc = 0;
    for (int v : vv) {
      if (edge[v]) continue;
      uc++;
      if (indegree[v] & 1) oc++;
    }
    if (oc != 2 || uc < 4) return cout << "NIE\n", void();
  }

  cout << "TAK\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
