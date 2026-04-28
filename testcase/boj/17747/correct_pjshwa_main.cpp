#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000, MOD = 1e9 + 7;
int B[MAXN + 1][MAXN + 1], N, M;
ll dp[MAXN + 1][MAXN + 1];
ll fac[MAXN + 1], ifac[MAXN + 1];

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

ll rec(int r, int c) {
  if (r == 0 && c == 0) return 1;
  if (dp[r][c] != -1) return dp[r][c];

  ll ret = 0;
  if (r > 0) {
    ll val = rec(r - 1, c) * fac[M - c] % MOD;
    ret = (ret + val) % MOD;
  }
  if (c > 0) {
    ll val = rec(r, c - 1) * fac[N - r] % MOD;
    ret = (ret + val) % MOD;
  }

  return dp[r][c] = ret;
}

void solve() {
  int K; cin >> N >> M >> K;

  int lx = N, ux = 1, ly = M, uy = 1;
  for (int i = 0; i < K; ++i) {
    int x, y; cin >> x >> y;
    B[x][y] = 1;

    lx = min(lx, x); ux = max(ux, x);
    ly = min(ly, y); uy = max(uy, y);
  }

  int cnt = 0;
  for (int x = lx; x <= ux; ++x) for (int y = ly; y <= uy; ++y) if (!B[x][y]) ++cnt;

  memset(dp, -1, sizeof(dp));
  int tx = N - (ux - lx + 1), ty = M - (uy - ly + 1);
  ll ans = rec(tx, ty);
  for (int i = 1; i <= cnt; ++i) ans = ans * i % MOD;

  ans = ans * C(tx, lx - 1) % MOD;
  ans = ans * C(ty, ly - 1) % MOD;
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
