#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n; cin >> n;
  ll q = sqrt(n);
  for (ll i = q - 2; i <= q + 2; i++) {
    if (i < 0) continue;
    if (i * i == n) return cout << "-1\n", void();
  }

  ll ans = 0;
  for (ll i = 1; i * i <= n; i++) {
    ll j = n - i * i;
    if (j < i * i) break;

    ll q = sqrt(j);
    for (ll k = q - 2; k <= q + 2; k++) {
      if (k < 0) continue;
      if (k * k == j) ans++;
    }
  }

  for (ll f = 1; f * f <= n; f++) {
    if (n % f) continue;

    ll u = f, v = n / f;
    if ((u + v) % 2) continue;

    ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
