#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int parent[MAX + 1][20], level[MAX + 1], p[MAX];
bool vis[MAX + 1];

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

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

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    graph[i].clear();
    vis[i] = level[i] = 0;
    for (int j = 0; j < 20; j++) parent[i][j] = 0;
  }

  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  for (int i = 0; i < n; i++) cin >> p[i];

  // fill parent array
  dfs(1, 0);
  for (int j = 0; j < 20; j++)
    for (int i = 2; i <= n; i++)
      if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];

  bool able = true;
  for (int i = 0; i < n - 1; i++) {
    int x = p[i], y = p[i + 1];
    int l = lca(x, y);
    int dist = level[x] + level[y] - 2 * level[l];
    able &= (dist <= 3);
  }
  cout << able << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
