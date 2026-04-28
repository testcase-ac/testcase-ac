#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

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

const int MOD = 1e9 + 7;

void solve() {
  ll k, p, q, r, s, a1; cin >> k >> p >> q >> r >> s >> a1;

  auto f = [&](ll l) -> ll {
    ll ret = a1 * lpow(p + r, l, MOD) % MOD;
    for (int i = 0; i < l; ++i) {
      ll cur = lpow(p + r, i, MOD) * (q + s) % MOD;
      ll mul = (1LL << (l - 1 - i)) % MOD;
      cur = cur * mul % MOD;
      ret = (ret + cur) % MOD;
    }
    return ret;
  };

  ll S = 0;
  for (int i = 0; i < k; ++i) S = (S + f(i)) % MOD;
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
