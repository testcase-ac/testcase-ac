#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

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

// https://codeforces.com/blog/entry/82953
ll upto(ll x, int n) {
  vector<ll> f{0}; ll cur = 0;
  for (int i = 1; i <= n + 1; i++) {
    cur = (cur + lpow(i, n, MOD)) % MOD;
    f.push_back(cur);
  }
  if (x <= n + 1) return f[x];

  ll coef = 1;
  for (int i = 1; i <= n + 1; i++) {
    coef = (coef * (x - i)) % MOD;
    coef = (coef * lpow(MOD - i, MOD - 2, MOD)) % MOD;
  }

  ll ans = 0;
  for (int i = 0; i <= n + 1; i++) {
    ans = (ans + f[i] * coef) % MOD;

    coef = (coef * (x - i)) % MOD;
    coef = (coef * lpow(x - i - 1, MOD - 2, MOD)) % MOD;

    ll den = (i + 1) % MOD;
    den = (den * lpow(MOD - (n + 1 - i), MOD - 2, MOD)) % MOD;
    coef = (coef * lpow(den, MOD - 2, MOD)) % MOD;
  }
  return ans;
}

void solve() {
  int a, b, d; cin >> a >> b >> d;

  ll ans = upto(b, d) - upto(a - 1, d);
  if (ans < 0) ans += MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
