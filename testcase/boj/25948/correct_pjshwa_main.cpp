#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
vector<int> graph[MAX + 1];
int indegree[MAX + 1];
bool vis[MAX + 1], is_cycle[MAX + 1];
int parent[MAX + 1], usz[MAX + 1], d[MAX + 1];

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

  if (x == y) return;
  if (usz[x] < usz[y]) swap(x, y);

  parent[y] = x;
  usz[x] += usz[y];
}

void cdfs(int v) {
  vis[v] = 1;
  for (int u : graph[v]) {
    if (!vis[u] && is_cycle[u]) {
      Union(v, u);
      cdfs(u);
    }
  }
}

int pdfs(int v) {
  if (d[v] != -1) return d[v];

  for (int u : graph[v]) {
    if (is_cycle[u]) return d[v] = usz[Find(u)] + 1;
    else return d[v] = pdfs(u) + 1;
  }

  return d[v] = 1;
}

void solve() {
  int m, n; cin >> m >> n;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    indegree[v]++;
  }

  queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (indegree[i] == 0) q.push(i);
  }
  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int u : graph[v]) {
      indegree[u]--;
      if (indegree[u] == 0) q.push(u);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (indegree[i] > 0) is_cycle[i] = 1;
  }

  iota(parent, parent + n, 0);
  fill(usz, usz + n, 1);
  for (int i = 0; i < n; ++i) {
    if (is_cycle[i]) cdfs(i);
  }

  memset(d, -1, sizeof d);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (indegree[i] == 0) ans = max(ans, pdfs(i));
    if (is_cycle[i]) ans = max(ans, usz[Find(i)]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
