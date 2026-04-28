#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5, MOD = 1e9 + 7;
ll fac[MAX + 1], ifac[MAX + 1];
ll d[MAX + 1];

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
  int n;
  cin >> n;

  d[0] = d[1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      ll addend = C(i - 1, j);
      addend = (addend * d[j]) % MOD;
      addend = (addend * d[i - 1 - j]) % MOD;
      d[i] = (d[i] + addend) % MOD;
    }
    d[i] = (d[i] * lpow(2, MOD - 2, MOD)) % MOD;
  }

  cout << d[n] << '\n';
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
