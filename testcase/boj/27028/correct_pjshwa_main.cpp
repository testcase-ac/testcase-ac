#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40000, MAXB = 20;
vector<pii> adj[MAXN + 1];
int parent[MAXN + 1][MAXB], cdist[MAXN + 1], level[MAXN + 1];

void dfs(int v, int p, int cd, int l) {
  level[v] = l, cdist[v] = cd;
  for (auto& [u, d] : adj[v]) {
    if (u == p) continue;
    parent[u][0] = v;
    dfs(u, v, cd + d, l + 1);
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
    for (int i = MAXB - 1; i >= 0; i--) {
      if (!parent[x][i] || parent[x][i] == parent[y][i]) continue;
      x = parent[x][i], y = parent[y][i];
    }
    x = parent[x][0];
  }
  return x;
}

void solve() {
  int N, M; cin >> N >> M;
  assert(N == M + 1);

  while (M--) {
    int u, v, d; string o; cin >> u >> v >> d >> o;
    adj[u].emplace_back(v, d);
    adj[v].emplace_back(u, d);
  }

  dfs(1, 0, 0, 0);
  for (int b = 0; b < MAXB - 1; ++b) {
    for (int i = 1; i <= N; ++i) {
      if (parent[i][b] == 0) continue;
      parent[i][b + 1] = parent[parent[i][b]][b];
    }
  }

  int K; cin >> K;
  while (K--) {
    int x, y; cin >> x >> y;
    int l = lca(x, y);
    cout << cdist[x] + cdist[y] - 2 * cdist[l] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
