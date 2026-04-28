#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 51;
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

void solve() {
  int N, M; cin >> N >> M;

  vector<pii> E;
  for (int i = 0; i < N - 1; i++) {
    int u, v; cin >> u >> v; u++; v++;
    graph[u].push_back(v);
    graph[v].push_back(u);
    E.push_back({u, v});
  }

  // fill parent array
  dfs(1, 0);
  for (int j = 0; j < 20; j++)
    for (int i = 2; i <= N; i++)
      if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];
      
  vector<int> P(M);
  for (int i = 0; i < M; i++) {
    cin >> P[i]; P[i]++;
  }

  double ans = 0;
  for (auto& [u, v] : E) {
    double prob = 1;
    for (int s : P) {
      int cnt = 0;
      for (int e = 1; e <= N; e++) {
        if (s == e) continue;
        if (in_way(u, s, e) && in_way(v, s, e)) cnt++;
      }
      prob *= (double)cnt / (N - 1);
    }
    ans += prob;
  }
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
