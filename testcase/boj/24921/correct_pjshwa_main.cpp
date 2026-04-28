#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1000, INF = 1e18;
vector<pll> adj[MAXN];
bool vis[MAXN];

pll maxd(int v, ll cd) {
  vis[v] = true;
  ll mv = v, md = cd;
  for (pll dst : adj[v]) {
    auto [v, d] = dst;
    if (vis[v]) continue;

    auto [dv, dd] = maxd(v, cd + d);
    if (md < dd) mv = dv, md = dd;
  }
  return {mv, md};
}

ll diameter_tree(int N) {
  fill(vis, vis + N, false);
  auto [mv, _md] = maxd(0, 0);
  fill(vis, vis + N, false);
  auto [_mv, md] = maxd(mv, 0);
  return md;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  for (int i = 0; i < N; ++i) adj[i].clear();

  ll ans = 0;
  for (int i = 0; i < N - 1; ++i) {
    int u, v, w; cin >> u >> v >> w; --u; --v;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
    ans += w;
  }
  cout << 2 * ans - diameter_tree(N) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
