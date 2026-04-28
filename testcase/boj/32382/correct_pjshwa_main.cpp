#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXV = 5000, BIAS = 2500, MOD = 1e9 + 7;
ll A[MAXN + 1], fac[MAXN + 1], ifac[MAXN + 1];
int dp[2][MAXN + 1][MAXV + 1];

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
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  dp[0][0][BIAS] = 1;
  for (int i = 1; i <= N; ++i) {
    int v = A[i], x = i & 1;
    memset(dp[x], 0, sizeof(dp[x]));
    for (int pc = 0; pc <= i; ++pc) for (int pv = v; pv <= MAXV; ++pv) {
      int nv = pv - v, nc = pc;
      dp[x][nc][nv] = (dp[x][nc][nv] + dp[x ^ 1][pc][pv]) % MOD;
    }
    for (int pc = 0; pc < i; ++pc) for (int pv = 0; pv + v <= MAXV; ++pv) {
      int nv = pv + v, nc = pc + 1;
      dp[x][nc][nv] = (dp[x][nc][nv] + dp[x ^ 1][pc][pv]) % MOD;
    }
  }

  int ans = 0;
  for (int k = 0; k <= N; ++k) {
    ll c = dp[N & 1][k][BIAS];
    c = (c * fac[N - k]) % MOD;
    c = (c * fac[k]) % MOD;
    ans = (ans + c) % MOD;
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
