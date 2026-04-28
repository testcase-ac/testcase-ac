#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40000;
vector<tuple<int, int, int>> adj[MAXN + 1];
int Px[MAXN + 1], Py[MAXN + 1], parent[MAXN + 1];

void dfs(int v, int p, int x, int y) {
  Px[v] = x; Py[v] = y;
  for (auto [u, dx, dy] : adj[v]) {
    if (u == p) continue;
    dfs(u, v, x + dx, y + dy);
  }
}

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

void solve() {
  int N, M; cin >> N >> M;
  assert(N == M + 1);

  vector<pii> edges;
  while (M--) {
    int u, v, d; string o; cin >> u >> v >> d >> o;
    int dx = 0, dy = 0;
    if (o == "N") dy = d;
    if (o == "S") dy = -d;
    if (o == "E") dx = d;
    if (o == "W") dx = -d;
    adj[u].emplace_back(v, dx, dy);
    adj[v].emplace_back(u, -dx, -dy);
    edges.emplace_back(u, v);
  }
  dfs(1, 0, 0, 0);

  int K; cin >> K;
  vector<tuple<int, int, int, int>> queries;
  for (int i = 0; i < K; ++i) {
    int u, v, x; cin >> u >> v >> x;
    queries.emplace_back(x - 1, u, v, i);
  }
  sort(queries.begin(), queries.end());

  vector<int> ans(K);
  iota(parent, parent + N + 1, 0); int ei = 0;
  for (auto& [x, u, v, i] : queries) {
    while (ei <= x) {
      auto [pu, pv] = edges[ei++];
      Union(pu, pv);
    }
    if (Find(u) != Find(v)) ans[i] = -1;
    else ans[i] = abs(Px[u] - Px[v]) + abs(Py[u] - Py[v]);
  }

  for (int i = 0; i < K; ++i) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
