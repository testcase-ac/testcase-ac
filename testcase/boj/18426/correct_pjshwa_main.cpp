#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1e9 + 7;
ll d[2][MAX + 1][MAX + 1], n;
ll fac[MAX + 1], ifac[MAX + 1];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

ll r(bool u, int v, int i) {
  if (i == 0) return u && v == 0;
  if (d[u][v][i] != -1) return d[u][v][i];

  ll res = 0;
  for (int j = 0; j <= v; j++) {
    ll addend = r(u || i == j, v - j, i - 1) * C(v, j) % MOD;
    res = (res + addend) % MOD;
  }

  return d[u][v][i] = res;
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
  cin >> n;
  memset(d, -1, sizeof(d));
  cout << r(0, n, n) << '\n';
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
