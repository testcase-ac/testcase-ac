#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll L, R, Q; cin >> L >> R >> Q;
  if (Q > R) return cout << "infinity\n", void();

  ll r = L / Q, x;
  if (R < (r + 1) * Q) x = Q * r;
  else x = Q;

  ll ans = 0;
  for (ll i = 1; i * i <= x; ++i) {
    if (x % i) continue;
    ++ans;
    if (i * i != x) ++ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
