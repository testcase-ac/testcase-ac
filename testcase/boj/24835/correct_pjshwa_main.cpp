#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
vector<int> graph[MAX + 1];
int parent[MAX + 1][20];
int level[MAX + 1];
bool vis[MAX + 1];

void dfs(int node, int lv) {
  vis[node] = true;
  level[node] = lv;

  for (int el : graph[node]) {
    if (!vis[el]) {
      parent[el][0] = node;
      dfs(el, lv + 1);
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

int dist(int x, int y) {
  return level[x] + level[y] - (2 * level[lca(x, y)]);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs(1, 0);
  for (int j = 0; j < 19; j++) for (int i = 2; i <= n; i++) {
    if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];
  }

  int q;
  cin >> q;
  while (q--) {
    int x, y, a, b, k;
    cin >> x >> y >> a >> b >> k;

    int o = dist(a, b);
    int p = min(dist(a, x) + dist(y, b), dist(a, y) + dist(x, b)) + 1;

    int res = INF;
    for (int d : {o, p}) {
      if (d % 2 == k % 2) res = min(res, d);
    }
    if (res <= k) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
