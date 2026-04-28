#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2.5e5;
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

bool in_way(int p, int x, int y) {
  int l = lca(x, y);
  return (
    (lca(x, p) == p && lca(y, p) == l) ||
    (lca(y, p) == p && lca(x, p) == l)
  );
}

int main() {
  fast_io();

  int n, m, x, y, r;
  cin >> n;
  assert(2 <= n && n <= MAX);

  set<pair<int, int>> edges;
  for (int i = 0; i < n - 1; i++) {
    cin >> x >> y;
    assert(1 <= x && x <= n);
    assert(1 <= y && y <= n);
    assert(x != y);
    graph[x].push_back(y);
    graph[y].push_back(x);
    edges.insert({min(x, y), max(x, y)});
  }

  // fill parent array
  dfs(1, 0);
  for (int j = 0; j < 20; j++)
    for (int i = 2; i <= n; i++)
      if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];

  cin >> m;
  assert(1 <= m && m <= MAX);
  while (m--) {
    int op, i, j;
    cin >> op >> i >> j;
    assert(op == 1 || op == 2);
    assert(1 <= i && i <= n);
    assert(1 <= j && j <= n);
    if (op == 1) {
      int k;
      cin >> k;
      assert(1 <= k && k <= n);
      cout << (in_way(k, i, j) ? "NO" : "YES") << '\n';
    }
    else {
      int k1, k2;
      cin >> k1 >> k2;
      assert(1 <= k1 && k1 <= n);
      assert(1 <= k2 && k2 <= n);
      assert(edges.count({min(k1, k2), max(k1, k2)}));
      cout << (in_way(k1, i, j) && in_way(k2, i, j) ? "NO" : "YES") << '\n';
    }
  }
}
