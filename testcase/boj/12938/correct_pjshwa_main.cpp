#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e4, MOD = 1e9 + 9;
ll fac[MAX + 1], ifac[MAX + 1];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

ll H(int n, int k) {
  return C(n + k - 1, k);
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

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int n, x;
  cin >> n;
  map<int, int> ft;

  for (int i = 0; i < n; i++) {
    cin >> x;

    while (x % 2 == 0) {
      ft[2]++;
      x /= 2;
    }
    for (ll d = 3; d * d <= x; d += 2) {
      while (x % d == 0) {
        ft[d]++;
        x /= d;
      }
    }
    if (x > 1) ft[x]++;
  }

  ll ans = 1;
  for (auto [k, v] : ft) {
    ans = (ans * H(n, v)) % MOD;
  }
  cout << ans << '\n';
}
