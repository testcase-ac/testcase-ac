#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 2e5, MOD = 1e9 + 7;
int a[MAX];
ll fac[MAX + 1], ifac[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

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
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  ll ans = 0;
  for (int i = k - 1; i < n; i++) {
    ll cur = (C(i, k - 1) * a[i]) % MOD;
    ans = (ans + cur) % MOD;
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
