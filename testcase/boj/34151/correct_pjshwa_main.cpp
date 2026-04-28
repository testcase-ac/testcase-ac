#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  ll p, a, b; cin >> p >> a >> b;

  if (a > b) swap(a, b);
  ll u = (b - 1) / a, B = lpow(p, a, MOD), ans;

  // sum of p^a, p^2a, ... p^ua;
  if (B == 1) ans = u % MOD;
  else ans = B * (lpow(B, u, MOD) - 1 + MOD) % MOD * lpow(B - 1, MOD - 2, MOD) % MOD;

  ans = (ans + lpow(p, b, MOD)) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
