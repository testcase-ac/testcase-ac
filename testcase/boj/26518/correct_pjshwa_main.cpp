#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll b, c, a1, a2;
  cin >> b >> c >> a1 >> a2;

  double ans = sqrt(b * b + 4 * c);
  ans += b;
  ans /= 2;
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
