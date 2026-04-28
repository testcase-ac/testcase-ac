#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15000, MOD = 1e9 + 7;
// int N, dp[MAXN + 10][MAXN + 10][MAXN + 10];
ll N, fc[MAXN + 1], gc[MAXN + 1];
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

ll f(int n) {
  if (fc[n] != -1) return fc[n];
  ll ret = fac[3 * n];
  for (int j = 0; j < 3; ++j) ret = (ret * ifac[n]) % MOD;
  return fc[n] = ret;
}

ll g(int n) {
  if (gc[n] != -1) return gc[n];
  ll ret = f(n);
  for (int i = 1; i < n; ++i) {
    ll cur = (f(i) * g(n - i)) % MOD;
    ret = (ret - cur + MOD) % MOD;
  }
  return gc[n] = ret;
}

// int rec(int uc, int dc, int pc) {
//   if (dp[uc][dc][pc] != -1) return dp[uc][dc][pc];

//   int t = uc + dc + pc;
//   cout << "t = " << t << ", uc = " << uc << ", dc = " << dc << ", pc = " << pc << '\n';
//   if (t == 3 * N) return dp[uc][dc][pc] = (uc == N && dc == N && pc == N);
//   if (uc > 0 && uc == dc && dc == pc) return dp[uc][dc][pc] = 0;

//   int ret = 0;
//   if (uc < N) ret = (ret + rec(uc + 1, dc, pc)) % MOD;
//   if (dc < N) ret = (ret + rec(uc, dc + 1, pc)) % MOD;
//   if (pc < N) ret = (ret + rec(uc, dc, pc + 1)) % MOD;
//   return dp[uc][dc][pc] = ret;
// }

void solve() {
  cin >> N;

  memset(fc, -1, sizeof(fc));
  memset(gc, -1, sizeof(gc));
  cout << g(N) << '\n';
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
