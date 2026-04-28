#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int parent[MAXN]; bool vis[MAXN];
vector<pii> adj[MAXN];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

pii maxd(int v, int cd) {
  vis[v] = true;
  int mv = v, md = cd;
  for (pii dst : adj[v]) {
    auto [v, d] = dst;
    if (vis[v]) continue;

    auto [dv, dd] = maxd(v, cd + d);
    if (md < dd) mv = dv, md = dd;
  }
  return {mv, md};
}

int diameter_tree() {
  memset(vis, 0, sizeof(vis));
  auto [mv, _md] = maxd(0, 0);
  memset(vis, 0, sizeof(vis));
  auto [_mv, md] = maxd(mv, 0);
  return md;
}

void solve() {
  int N, M; cin >> N >> M;
  iota(parent, parent + N, 0);

  vector<tuple<int, int, int>> edges;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    edges.emplace_back(w, u, v);
  }
  sort(edges.begin(), edges.end());

  int ans = 0;
  for (auto [w, u, v] : edges) {
    if (Find(u) == Find(v)) continue;
    Union(u, v); ans += w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  cout << ans << '\n';
  cout << diameter_tree() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
