#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 4e6, MOD = 1e9 + 7;
ll fac[MAXN + 1], ifac[MAXN + 1];
const int dx[6] = {0, 0, -1, -1, 1, 1};
const int dy[6] = {-1, 1, -1, 0, 0, 1};

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
  int N; cin >> N;
  if (N == 2) return cout << "0 3\n", void();
  if (N == 3) return cout << "1 4\n", void();
  if (N == 4) return cout << "2 4\n", void();
  if (N == 5) return cout << "3 6\n", void();
  // if (N == 6) return cout << "6 2\n", void();

  // ll maxd = 0;
  // for (int r = 0; r < N; ++r) for (int c = 0; c <= r; ++c) {
  //   ll val = C(r, c);
  //   for (int k = 0; k < 6; ++k) {
  //     int nr = r + dx[k], nc = c + dy[k];
  //     if (nr < 0 || nc < 0 || nr >= N || nc > nr) continue;
  //     ll nval = C(nr, nc);
  //     maxd = max(maxd, abs(val - nval));
  //   }
  // }

  // ll tcnt = 0;
  // for (int r = 0; r < N; ++r) for (int c = 0; c <= r; ++c) {
  //   ll val = C(r, c);
  //   for (int k = 0; k < 6; ++k) {
  //     int nr = r + dx[k], nc = c + dy[k];
  //     if (nr < 0 || nc < 0 || nr >= N || nc > nr) continue;
  //     ll nval = C(nr, nc);
  //     ll d = abs(val - nval);
  //     tcnt += d == maxd;
  //   }
  // }

  // cout << maxd << ' ' << tcnt / 2 << '\n';

  ll r = N - 2;
  ll maxd = C(r, r / 2), tcnt = 2 * (1 + (r & 1));
  cout << maxd << ' ' << tcnt << '\n';
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
