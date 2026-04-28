#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e5;
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

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  // fill parent array
  dfs(1, 0);
  for (int j = 0; j < 20; j++)
    for (int i = 2; i <= n; i++)
      if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];

  while (q--) {
    int a, b, c;
    cin >> a >> b >> c;

    ll d1 = level[a] + level[b] - 2 * level[lca(a, b)];
    ll d2 = level[a] + level[c] - 2 * level[lca(a, c)];
    ll d3 = level[b] + level[c] - 2 * level[lca(b, c)];

    ll ad = d2, bd = d1 + d3;
    ll cd = (bd - ad) / 2;

    cout << (ad + cd + 1) * (ad + cd) / 2 + (cd + 1) * cd / 2 << '\n';
  }
}
