#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e6, MOD = 1e9 + 7;
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

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<pii> bombs(K);
  for (int i = 0; i < K; ++i) cin >> bombs[i].first >> bombs[i].second;
  sort(bombs.begin(), bombs.end());

  ll ans = 0;
  for (int s = 0; s < (1 << K); ++s) {
    ll cur = 1, x = 0, y = 0, flag = 0;
    for (int i = 0; i < K; ++i) {
      if (!(s & (1 << i))) continue;
      auto [bx, by] = bombs[i];
      cur = (cur * C(bx + by - x - y, bx - x)) % MOD;
      x = bx, y = by;
      flag = 1 - flag;
    }
    cur = (cur * C(N + M - x - y, N - x)) % MOD;
    if (flag) cur = (MOD - cur) % MOD;
    ans = (ans + cur) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAXN] = lpow(fac[MAXN], MOD - 2, MOD);
  for (int i = MAXN - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
