#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 4e6, MOD = 1e9 + 7;
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

ll D(int n, int k) {
  ll val = C(n + k, k);
  val = (val * (n - k + 1)) % MOD;
  val = (val * lpow(n + 1, MOD - 2, MOD)) % MOD;
  return val;
}

void solve() {
  int N, K; cin >> N >> K;

  ll ans = 0;
  for (int i = 0; i <= N; ++i) {
    ll coef = D(2 * N - i, i);
    ll val = lpow(N - i, K, MOD);
    ans = (ans + coef * val) % MOD;
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
