#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6, MOD = 998244353;
ll fac[MAX + 1], ifac[MAX + 1];
int a[MAX];

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

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!a[i]) continue;
    ll addend = C(n - 1, i);

    for (int k : {i, n - 1 - i}) {
      if (!k) continue;
      int d = 2 * k - 1;
      addend = (addend * fac[d]) % MOD;
      int inv2 = lpow(2, MOD - 2, MOD);
      addend = (addend * lpow(inv2, d / 2, MOD)) % MOD;
      addend = (addend * ifac[d / 2]) % MOD;
    }
    ans = (ans + addend) % MOD;
  }
  cout << ans << '\n';
}
