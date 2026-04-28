#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, MOD = 1e9 + 7;
ll fac[MAX + 1], ifac[MAX + 1];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
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

void solve() {
  int D, N; cin >> D >> N;
  if (D == 1) return cout << "1\n", void();
  // if (D == 2) return cout << N + 1 << '\n', void();

  ll ans = fac[D * N];
  for (int i = 0; i < N; ++i) {
    ans = (ans * fac[i]) % MOD;
    ans = (ans * lpow(fac[D + i], MOD - 2, MOD)) % MOD;
  }

  // for (int i = 1; i <= N * D; ++i) ans = (ans * i) % MOD;
  // ans = (ans * lpow(lpow(fac[N], D, MOD), MOD - 2, MOD)) % MOD;

  ll denom = 1;
  for (int i = 0; i < D; ++i) {
    denom = (denom * C(N * (D - i), N)) % MOD;
  }
  ans = (ans * lpow(denom, MOD - 2, MOD)) % MOD;

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
