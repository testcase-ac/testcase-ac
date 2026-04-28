#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 2e18;
ll c[MAX + 1];
pii g[MAX + 1];

void dfs(int v) {
  cout << v << ' ';
  auto [u, w] = g[v];
  if (u) dfs(u);
  if (u) dfs(u);
  if (w) dfs(w);
}

ll mark_cnt(int v) {
  ll res = 1;
  auto [u, w] = g[v];
  if (u) res += 2 * mark_cnt(u);
  if (w) res += mark_cnt(w);
  return c[v] = min(res, INF);
}

void r(int v, ll k) {
  k--;
  if (k == 0) return cout << v << '\n', void();
  auto [u, w] = g[v];
  if (u == 0) r(w, k);
  else {
    if (w == 0) {
      if (k > c[u]) k -= c[u];
      r(u, k);
    }
    else {
      if (k > 2 * c[u]) r(w, k - 2 * c[u]);
      else if (k > c[u]) r(u, k - c[u]);
      else r(u, k);
    }
  }
}

void solve() {
  int n;
  ll k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> g[i].first >> g[i].second;
  // dfs(1);
  mark_cnt(1);
  // for (int i = 1; i <= n; i++) cout << c[i] << ' ';
  // cout << '\n';
  r(1, k);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
