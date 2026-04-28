#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  double d1, d2, x; cin >> d1 >> d2 >> x;
  if (d1 < d2) swap(d1, d2);

  double u = d2 * x / (d1 * (100 - x));
  double ans = (d1 * u + d2) / (u + 1);
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
