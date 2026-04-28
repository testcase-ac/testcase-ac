#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
vector<pii> graph[MAX + 1];
int parent[MAX + 1][20];
int level[MAX + 1];
ll depth[MAX + 1];
bool vis[MAX + 1];

void dfs(int node, int lv, ll dpt) {
  vis[node] = true;
  level[node] = lv;
  depth[node] = dpt;

  for (auto [el, d] : graph[node]) {
    if (!vis[el]) {
      parent[el][0] = node;
      dfs(el, lv + 1, dpt + d);
    }
  }
}

int lca(int x, int y) {
  if (level[x] < level[y]) swap(x, y);
  int diff = level[x] - level[y];

  for (int i = 0; diff; i++) {
    if (diff % 2) x = parent[x][i];
    diff /= 2;
  }

  // level[x] = level[y] from now on.
  if (x != y) {
    for (int i = 19; i >= 0; i--) {
      if (!parent[x][i] || parent[x][i] == parent[y][i]) continue;

      x = parent[x][i];
      y = parent[y][i];
    }

    x = parent[x][0];
  }
  
  return x;
}

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    graph[a].push_back({b, w});
    graph[b].push_back({a, w});
  }

  dfs(1, 0, 0);
  for (int j = 0; j <= 19; j++) for (int i = 2; i <= n; i++) {
    if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];
  }

  while (q--) {
    int u, v;
    cin >> u >> v;

    ll d = depth[u] + depth[v] - 2 * depth[lca(u, v)];
    if (d & 1) {
      cout << "-1\n";
      continue;
    }

    if (depth[u] < depth[v]) swap(u, v);
    ll t = depth[u] - d / 2;

    for (int i = 19; i >= 0; i--) {
      if (parent[u][i] && depth[parent[u][i]] >= t) u = parent[u][i];
    }

    if (depth[u] == t) cout << u << '\n';
    else cout << "-1\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
