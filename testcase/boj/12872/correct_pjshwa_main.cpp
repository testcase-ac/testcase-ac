#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, MOD = 1e9 + 7;
ll fac[MAX + 1], ifac[MAX + 1];

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

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

// n songs total, make a playlist of p songs
// two occurrences of the same song must be separated by at least m other songs
ll f(int n, int m, int p) {
  ll ret = 1;
  for (int i = 0; i < min(m, p); i++) ret = (ret * (n - i)) % MOD;
  for (int i = 0; i < p - min(m, p); i++) ret = (ret * (n - m)) % MOD;
  return ret;
}

void solve() {
  int N, M, P; cin >> N >> M >> P;

  ll ans = 0; int sgn = 1;
  for (int i = N; i >= 1; i--) {
    ll cur = C(N, i) * f(i, M, P) % MOD;
    cur = (cur * sgn + MOD) % MOD;
    ans = (ans + cur) % MOD;
    sgn *= -1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
