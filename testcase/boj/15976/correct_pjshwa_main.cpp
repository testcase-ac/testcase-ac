#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m, a, b;
  cin >> n;
  vector<pii> xs, yp;
  for (int i = 0; i < n; i++) {
    int xi, xv;
    cin >> xi >> xv;
    xs.emplace_back(xi, xv);
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    int yi, yv;
    cin >> yi >> yv;
    yp.emplace_back(yi, yv);
  }
  for (int i = 1; i < m; i++) yp[i].second += yp[i - 1].second;
  cin >> a >> b;

  ll ans = 0;
  for (auto [xi, xv] : xs) {
    auto itl = lower_bound(yp.begin(), yp.end(), pii(xi + a, 0));
    auto itu = upper_bound(yp.begin(), yp.end(), pii(xi + b, 1e9));

    int lb = itl == yp.begin() ? 0 : itl[-1].second;
    int ub = itu == yp.begin() ? 0 : itu[-1].second;
    ans += (ll)xv * (ub - lb);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
