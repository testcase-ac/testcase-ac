#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXV = 1e6 + 2, MOD = 1e6 + 3;
int X[MAXN], Y[MAXN], N, M, L;
ll dp1[MAXN], dp2[MAXN][MAXN + 1];
ll fac[MAXV + 1], ifac[MAXV + 1];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  if (n >= MOD) {
    return C(n / MOD, k / MOD) * C(n % MOD, k % MOD) % MOD;
  }
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

int rec1(int v) {
  if (dp1[v] != -1) return dp1[v];

  int ret = 1;
  for (int u = 0; u < L; ++u) {
    if (u == v || X[u] < X[v] || Y[u] < Y[v]) continue;
    ret = max(ret, rec1(u) + 1);
  }
  return dp1[v] = ret;
}

ll rec2(int v, int t) {
  if (t == 0) {
    int xd = N - X[v], yd = M - Y[v];
    return C(xd + yd, xd);
  }
  if (dp2[v][t] != -1) return dp2[v][t];

  ll ret = 0;
  for (int u = 0; u < L; ++u) {
    if (u == v || X[u] < X[v] || Y[u] < Y[v]) continue;

    ll add = rec2(u, t - 1) * C(X[u] - X[v] + Y[u] - Y[v], X[u] - X[v]) % MOD;
    ret = (ret + add) % MOD;
  }
  return dp2[v][t] = ret;
}

void solve() {
  cin >> N >> M >> L;
  for (int i = 0; i < L; ++i) cin >> X[i] >> Y[i];

  memset(dp1, -1, sizeof(dp1)); int maxl = 0;
  for (int i = 0; i < L; ++i) maxl = max(maxl, rec1(i));

  memset(dp2, -1, sizeof(dp2)); ll ans = 0;
  for (int i = 0; i < L; ++i) {
    ll add = rec2(i, maxl - 1) * C(X[i] + Y[i] - 2, X[i] - 1) % MOD;
    ans = (ans + add) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAXV; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAXV] = lpow(fac[MAXV], MOD - 2, MOD);
  for (int i = MAXV - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
