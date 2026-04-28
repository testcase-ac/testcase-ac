#include <bits/stdc++.h>
#include "../../debug.h"
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<pii> graph[MAX + 1];
ll par[MAX + 1][20], dis[MAX + 1][20];
tii mxe[MAX + 1][20];
int lev[MAX + 1];

void dfs(int v, int p, int lv) {
  lev[v] = lv;
  for (auto [u, d] : graph[v]) {
    if (u == p) continue;
    par[u][0] = v;
    dis[u][0] = d;
    mxe[u][0] = {d, u, v};
    dfs(u, v, lv + 1);
  }
}

int lca(int x, int y) {
  if (lev[x] < lev[y]) swap(x, y);
  int diff = lev[x] - lev[y];

  for (int i = 0; diff; i++) {
    if (diff % 2) x = par[x][i];
    diff /= 2;
  }

  // lev[x] = lev[y] from now on.
  if (x != y) {
    for (int i = 19; i >= 0; i--) {
      if (!par[x][i] || par[x][i] == par[y][i]) continue;

      x = par[x][i];
      y = par[y][i];
    }

    x = par[x][0];
  }
  
  return x;
}

ll dist(int x, int y) {
  int l = lca(x, y), px = x, py = y;
  int xd = lev[x] - lev[l], yd = lev[y] - lev[l];

  ll ret = 0;
  for (int i = 19; i >= 0; i--) {
    if (xd < (1 << i)) continue;
    xd -= (1 << i);
    ret += dis[px][i];
    px = par[px][i];
  }
  for (int i = 19; i >= 0; i--) {
    if (yd < (1 << i)) continue;
    yd -= (1 << i);
    ret += dis[py][i];
    py = par[py][i];
  }

  return ret;
}

bool vtx_in_way(int p, int x, int y) {
  int l = lca(x, y);
  return (
    (lca(x, p) == p && lca(y, p) == l) ||
    (lca(y, p) == p && lca(x, p) == l)
  );
}

bool path_in_way(int s, int e, int x, int y) {
  return vtx_in_way(s, x, y) && vtx_in_way(e, x, y);
}

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    graph[u].push_back({v, c});
    graph[v].push_back({u, c});
  }

  dfs(1, -1, 0);
  for (int j = 0; j < 20; j++) for (int i = 2; i <= n; i++) {
    if (!par[i][j]) continue;
    par[i][j + 1] = par[par[i][j]][j];
    dis[i][j + 1] = dis[i][j] + dis[par[i][j]][j];
    mxe[i][j + 1] = max(mxe[i][j], mxe[par[i][j]][j]);
  }

  while (q--) {
    int u, v, w, a, b;
    cin >> u >> v >> w >> a >> b;

    int l = lca(u, v);
    int ud = lev[u] - lev[l], vd = lev[v] - lev[l];
    int pu = u, pv = v;

    tii del_edge = {0, 0, 0};
    for (int i = 19; i >= 0; i--) {
      if (ud < (1 << i)) continue;
      ud -= (1 << i);
      del_edge = max(del_edge, mxe[pu][i]);
      pu = par[pu][i];
    }
    for (int i = 19; i >= 0; i--) {
      if (vd < (1 << i)) continue;
      vd -= (1 << i);
      del_edge = max(del_edge, mxe[pv][i]);
      pv = par[pv][i];
    }

    auto [_, s, e] = del_edge;
    if (path_in_way(s, e, a, b)) {
      if (!path_in_way(s, e, a, u) && !path_in_way(s, e, b, v)) {
        cout << dist(a, u) + w + dist(v, b) << '\n';
      }
      else if (!path_in_way(s, e, a, v) && !path_in_way(s, e, b, u)) {
        cout << dist(a, v) + w + dist(u, b) << '\n';
      }
      else {
        assert(0);
      }
    }
    else cout << dist(a, b) << '\n';
  }
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
