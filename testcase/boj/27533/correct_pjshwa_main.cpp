#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, MOD = 1e9 + 7;
ll fac[MAX + 1], ifac[MAX + 1];

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

ll H(int n, int k) {
  return C(n + k - 1, k);
}

ll Catalan(int n) {
  return C(2 * n, n) * lpow(n + 1, MOD - 2, MOD) % MOD;
}

void solve() {
  int N, M;
  cin >> N >> M;
  N--, M--;
  if (N > M) swap(N, M);

  ll ans = 0;
  for (int i = 0; i <= N - 1; i++) {
    ll cur = Catalan(i);
    cur = (cur * H(2 * i + 1, N - i - 1)) % MOD;
    cur = (cur * H(N + i, M - i - 1)) % MOD;
    ans = (ans + cur) % MOD;
  }

  ans = (ans * 2) % MOD;
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
