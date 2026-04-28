#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  double x, t;
  cin >> x >> t;

  double ans = max(t * 5.0 * x / 6, t * 200.0 / 3);
  double opt_sleep = t * (200.0 - 2 * x - 25) / (300.0 - 3 * x);
  if (opt_sleep >= t / 6 && opt_sleep <= t / 3) {
    ans = max(ans, ((100 - x) * 6.0 / t * (opt_sleep - t / 6) + x) * (t - opt_sleep));
  }

  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
