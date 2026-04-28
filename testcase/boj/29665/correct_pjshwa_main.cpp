#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll fac[MAXN + 1], ifac[MAXN + 1];

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

ll C(int n, int k, int mod) {
  if (n < 0 || k < 0 || n < k) return 0;
  if (n >= mod) {
    return C(n / mod, k / mod, mod) * C(n % mod, k % mod, mod) % mod;
  }
  return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}

void solve() {
  int n, k, MOD; cin >> n >> k >> MOD;
  int L = min(n, MOD - 1);

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= L; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[L] = lpow(fac[L], MOD - 2, MOD);
  for (int i = L - 1; i > 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  cout << C(n - k + 1, k, MOD) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
