#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000, MOD = 1e9 + 7;
ll fac[MAXN + 1], ifac[MAXN + 1], dfac[MAXN + 1];

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

ll Catalan(int n) {
  return fac[2 * n] * ifac[n + 1] % MOD * ifac[n] % MOD;
}

int N;
void solve() {
  ll ans = 0;
  for (int i = 1; i <= N; ++i) {
    ll cur = C(2 * N - 2, 2 * i - 2) % MOD;
    for (ll s : {i - 1, N - i}) cur = cur * dfac[s] % MOD;
    cur = cur * (2 * N - 1) % MOD;
    ans = (ans + cur) % MOD;
  }
  ans = ans * lpow(2, N, MOD) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAXN] = lpow(fac[MAXN], MOD - 2, MOD);
  for (int i = MAXN - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  dfac[0] = dfac[1] = 1;
  for (int i = 2; i <= MAXN; i++) dfac[i] = (dfac[i - 1] * (2 * i - 1)) % MOD;

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
