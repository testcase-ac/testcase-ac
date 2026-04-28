#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e5, INF = 1e18;
vector<pii> graph[MAX + 1];
ll d1[MAX + 1], d2[MAX + 1], sz[MAX + 1];

ll dfs1(int v, int p) {
  sz[v] = 1;
  for (auto [u, w] : graph[v]) {
    if (u == p) continue;
    d1[v] += dfs1(u, v) + w * sz[u];
    sz[v] += sz[u];
  }
  return d1[v];
}

void dfs2(int v, int p, ll h) {
  d2[v] = h;
  for (auto [u, w] : graph[v]) {
    if (u == p) continue;
    dfs2(u, v, h + w * (sz[1] - 2 * sz[u]));
  }
}

void solve() {
  ll N1;
  cin >> N1;
  for (int i = 0; i < N1 - 1; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    graph[u].emplace_back(v, d);
    graph[v].emplace_back(u, d);
  }

  dfs1(1, 0);
  dfs2(1, 0, d1[1]);
  ll R1 = INF, V1 = -1;
  for (int i = 1; i <= N1; i++) {
    if (d2[i] < R1) R1 = d2[i], V1 = i;
  }

  ll N2;
  cin >> N2;
  for (int i = 1; i <= N2; i++) graph[i].clear();
  for (int i = 0; i < N2 - 1; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    graph[u].emplace_back(v, d);
    graph[v].emplace_back(u, d);
  }
  memset(d1, 0, sizeof(d1));
  memset(d2, 0, sizeof(d2));
  memset(sz, 0, sizeof(sz));

  dfs1(1, 0);
  dfs2(1, 0, d1[1]);
  ll R2 = INF, V2 = -1;
  for (int i = 1; i <= N2; i++) {
    if (d2[i] < R2) R2 = d2[i], V2 = i;
  }

  cout << V1 << ' ' << V2 << '\n';
  cout << N1 * R2 + N2 * R1 + N1 * N2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
