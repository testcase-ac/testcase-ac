#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int parent[MAX + 1], inv[MAX + 1];
bool is_cycle[MAX + 1], vis[MAX + 1];
vector<tuple<int, int, int>> adj[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x); y = Find(y);
  if (x != y) parent[x] = y;
}

void dfs(int v, int ei) {
  vis[v] = 1;
  for (auto [u, w, i] : adj[v]) {
    if (ban[i]) continue;

    if (!vis[u]) inv[u] = v, dfs(u, i);
    else if (u != inv[v] && !is_cycle[u]) {
      // Cycle is detected
      for (int x = v; x != u; x = inv[x]) is_cycle[x] = 1;
      is_cycle[u] = 1;
    }
  }
}

void solve() {
  int n, m; cin >> n >> m;

  vector<tuple<int, int, int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    edges.push_back({w, u, v, i});

    if (i >= n - 1) continue;
    adj[u].push_back({v, w, i});
    adj[v].push_back({u, w, i});
  }
  sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
    auto [aw, au, av, ai] = a; auto [bw, bu, bv, bi] = b;
    if (aw != bw) return aw < bw;
    return ai < bi;
  });

  iota(parent, parent + n + 1, 0);
  queue<int> wait;
  for (auto [w, u, v, i] : edges) {
    if (Find(u) == Find(v)) continue;
    Union(u, v);
    if (i >= n - 1) wait.push(i);
  }

  cout << wait.size() << '\n';
  while (!wait.empty()) {
    int t = wait.front(); wait.pop();

    auto [w, u, v, i] = edges[t];
    adj[u].push_back({v, w, i});
    adj[v].push_back({u, w, i});
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
