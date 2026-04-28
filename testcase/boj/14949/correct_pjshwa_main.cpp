#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 600, MOD = 1e9 + 7;
ll d[6][MAX + 1];
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
  int H, W;
  cin >> H >> W;

  d[0][1] = 1;
  for (int h = 1; h <= H; h++) for (int p = 1; p <= W; p++) for (int i = 1; i <= W; i++) {
    ll addend = (d[h - 1][p] * C(p + i - 1, i)) % MOD;
    d[h][i] = (d[h][i] + addend) % MOD;
  }

  ll ans = 0;
  for (int i = 1; i <= W; i++) ans = (ans + d[H][i]) % MOD;
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
