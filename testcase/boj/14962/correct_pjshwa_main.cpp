#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 50, MAXD = 2e5, INF = 1e18;
vector<pii> adj[MAXN + 1];
ll H[MAXN + 1], dp[MAXN + 1][MAXD + 1];
vector<vector<ll>> costs;

void f() {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; ++i) adj[i].clear();

  for (int i = 1; i <= n; ++i) cin >> H[i];
  for (int j = 0; j < m; ++j) {
    int u, v, g; cin >> u >> v >> g;
    adj[u].emplace_back(v, g);
  }

  // init
  for (int u = 1; u <= n; ++u) for (int d = 0; d <= MAXD; ++d) dp[u][d] = INF;
  dp[1][0] = 0;

  for (int d = 0; d < MAXD; ++d) for (int u = 1; u <= n; ++u) {
    dp[u][d + 1] = min(dp[u][d + 1], dp[u][d] + H[u]);
    for (auto [v, g] : adj[u]) dp[v][d + 1] = min(dp[v][d + 1], dp[u][d] + g);
  }

  int a; cin >> a; vector<ll> c;
  for (int d = 0; d <= MAXD; ++d) c.push_back(dp[a][d]);
  costs.push_back(c);
}

void solve() {
  int p; cin >> p;
  for (int t = 0; t < p; ++t) f();

  ll ans = INF;
  for (int d = 0; d <= MAXD; ++d) {
    int ok = 1;
    for (int t = 0; t < p; ++t) ok &= (costs[t][d] != INF);
    if (!ok) continue;

    ll sum = 0;
    for (int t = 0; t < p; ++t) sum += costs[t][d];
    ans = min(ans, sum);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
