#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5, MOD = 1e9 + 7;
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
  int N;
  cin >> N;

  ll ans = 0;
  for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) for (int k = j + 1; k <= N; k++) {
    int d1 = j - i - 1, d2 = k - j - 1, d3 = N - k + i - 1;
    assert(d1 + d2 + d3 == N - 3);

    ll cur = fac[N - 3];
    cur = cur * ifac[d1] % MOD;
    cur = cur * ifac[d2] % MOD;
    cur = cur * ifac[d3] % MOD;
    if (d1 > 1) cur = (cur * lpow(2, d1 - 1, MOD)) % MOD;
    if (d2 > 1) cur = (cur * lpow(2, d2 - 1, MOD)) % MOD;
    if (d3 > 1) cur = (cur * lpow(2, d3 - 1, MOD)) % MOD;
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
