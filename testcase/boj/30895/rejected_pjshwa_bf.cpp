#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll X, Y, K; cin >> X >> Y >> K;

  ll L = X * (X + Y);
  ll d = -1, n = -1;
  for (ll m = K; m <= K + L; ++m) {
    ll cn = (m - 1) / X + 1;
    ll cd = (m - 1) / (Y + X) + 1;
    if (n == -1 || n * cd > cn * d) {
      n = cn;
      d = cd;
    }
  }

  ll ans = 1e18;
  for (ll m = K; m <= K + L; ++m) {
    ll cn = (m - 1) / X + 1;
    ll cd = (m - 1) / (Y + X) + 1;
    if (n * cd == cn * d) {
      ans = min(ans, m);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
