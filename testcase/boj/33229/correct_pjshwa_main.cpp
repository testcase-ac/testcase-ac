#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 313109;
ll fac[MOD], ifac[MOD];

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

ll C(ll n, ll k, ll p) {
  if (n < 0 || k < 0 || n < k) return 0;
  if (k == 0 || k == n) return 1;

  // Lucas theorem for prime modulus
  if (n >= p) return C(n / p, k / p, p) * C(n % p, k % p, p) % p;
  return fac[n] * ifac[k] % p * ifac[n - k] % p;
}

void solve() {
  ll N; cin >> N; N /= 2;

  // Cat(N) = C(2N, N) - C(2N, N - 1)
  ll ans = (C(2 * N, N, MOD) - C(2 * N, N - 1, MOD) + MOD) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i < MOD; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MOD - 1] = lpow(fac[MOD - 1], MOD - 2, MOD);
  for (int i = MOD - 2; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
