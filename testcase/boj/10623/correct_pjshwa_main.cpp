#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int level[MAX + 1], parent[MAX + 1][20];
bool vis[MAX + 1];
vector<int> order;

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
  int n, x;
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> x;
    graph[x].push_back(i);
  }

  queue<int> q;
  q.push(1);
  vis[1] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    order.push_back(cur);
    for (int next : graph[cur]) vis[next] = true, q.push(next);
  }

  memset(vis, 0, sizeof vis);

  // fill parent array
  dfs(1, 0);
  for (int j = 0; j < 20; j++)
    for (int i = 2; i <= n; i++)
      if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];

  int sz = order.size();
  ll ans = 0;
  for (int i = 0; i < sz - 1; i++) {
    int x = order[i], y = order[i + 1];
    ans += (ll)level[x] + level[y] - 2 * level[lca(x, y)];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
