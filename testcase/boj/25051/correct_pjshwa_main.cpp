#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 9e18;
tuple<ll, ll, ll> a[MAX];
int n, m;

ll solve_for(ll p) {
  ll res = -INF, cur = 0;
  int ep = 0;
  for (int sp = 0; sp < 2 * n; sp++) {
    auto& [xi, yi, si] = a[sp % n];

    while (ep < 2 * n) {
      auto& [xj, yj, sj] = a[ep % n];
      if (xi * xj + yi * yj < 0 || yi * xj - xi * yj < 0) break;
      if (xj * xj + yj * yj <= p) cur += sj;
      ep++;
    }

    res = max(res, cur);
    if (xi * xi + yi * yi <= p) cur -= si;
  }
  return res - p;
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    ll xi, yi, si;
    cin >> xi >> yi >> si;
    a[i] = {xi, yi, si};
  }

  // Clockwise sort
  sort(a, a + n, [] (const auto& lhs, const auto& rhs) {
    auto& [lxi, lyi, lsi] = lhs;
    auto& [rxi, ryi, rsi] = rhs;

    if (lxi >= 0 && rxi < 0) return true;
    if (lxi < 0 && rxi >= 0) return false;
    if (lxi == 0 && rxi == 0) {
      if (lyi >= 0 || ryi >= 0) return lyi > ryi;
      return ryi > lyi;
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    ll det = lxi * ryi - rxi * lyi;
    if (det < 0) return true;
    if (det > 0) return false;

    // Two points are on the same line
    // No further sorting necessary
    return lsi < rsi;
  });

  ll ans = -INF;
  for (int i = 0; i < m; i++) {
    ll p; cin >> p;
    ans = max(ans, solve_for(p));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
