#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2.5e5, INF = 1e18;
vector<tii> adj[MAXN + 1];
ll maxd[MAXN + 1][2], N;

void dfs(int v, int p, int x) {
  maxd[v][0] = 0; maxd[v][1] = -INF;
  for (auto& [u, c, a] : adj[v]) {
    if (u == p) continue;
    dfs(u, v, x);

    ll cost = c + a * (ll)x;
    ll val = maxd[u][0] + cost;
    if (val > maxd[v][0]) {
      maxd[v][1] = maxd[v][0];
      maxd[v][0] = val;
    }
    else if (val > maxd[v][1]) {
      maxd[v][1] = val;
    }
  }
}

ll f(int x) {
  dfs(1, 0, x); ll ret = 0;
  for (int i = 1; i <= N; ++i) ret = max(ret, maxd[i][0] + maxd[i][1]);
  return ret;
}

void solve() {
  int D; cin >> N >> D;
  for (int i = 0; i < N - 1; ++i) {
    int s, e, c, a; cin >> s >> e >> c >> a;
    adj[s].emplace_back(e, c, a);
    adj[e].emplace_back(s, c, a);
  }

  ll left = 0, right = D + 1;
  while (left + 3 <= right) {
    ll mid1 = left + (right - left) / 3;
    ll mid2 = right - (right - left) / 3;
    if (f(mid1) <= f(mid2)) right = mid2;
    else left = mid1;
  }

  ll ans = LLONG_MAX, ansi = -1;
  for (ll i = left; i <= right; ++i) {
    if (i < 0 || i > D) continue;
    ll res = f(i);
    if (res < ans) ans = res, ansi = i;
  }
  cout << ansi << '\n' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
