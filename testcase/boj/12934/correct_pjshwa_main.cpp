#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll x, y; cin >> x >> y;
  ll s = 2 * (x + y), q = sqrt(s);
  if (q * q + q != s) return cout << "-1\n", void();

  int ans = 0;
  for (int i = q; i >= 1; i--) {
    if (x >= i) x -= i, ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
