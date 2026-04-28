#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int k;
  cin >> k;

  double ans = 25 + 0.01 * k;
  ans = max(ans, 100.0);
  ans = min(ans, 2000.0);
  cout << fixed << setprecision(2) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
