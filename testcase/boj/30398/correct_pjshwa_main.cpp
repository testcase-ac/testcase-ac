#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6, MOD = 1e9 + 7;
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

void solve() {
  int N, d, P; cin >> N >> d >> P;

  vector<int> D(d, 1); ll ans = 1;
  for (int i = 0; i <= P; ++i) {
    ll tot = 0, cur = 1, x;
    for (int j = 0; j < d; ++j) {
      if (i == P) x = N;
      else cin >> x;
      ll dif = x - D[j]; assert(dif >= 0);
      tot += dif; cur = cur * ifac[dif] % MOD;
      D[j] = x;
    }
    cur = cur * fac[tot] % MOD;
    ans = ans * cur % MOD;
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
