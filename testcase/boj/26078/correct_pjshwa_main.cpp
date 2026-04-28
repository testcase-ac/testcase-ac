#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 18, MOD = 998244353;
int A[MAX], W[18];
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

void solve() {
  int K;
  cin >> K;

  int S = 1 << K;
  for (int i = 0; i < S; i++) cin >> A[i];
  for (int i = 0; i < K; i++) cin >> W[i];

  int l = 0;
  for (int i = 1; i < S; i++) {
    if (A[i] < A[0]) l++;
  }

  ll ans = 0, p = 2;
  for (int k = 0; k < K; k++) {
    ll cur = C(l, p - 1);
    cur = (cur * fac[S - p]) % MOD;
    cur = (cur * fac[p - 1]) % MOD;
    ans = (ans + cur * W[k]) % MOD;
    p <<= 1;
  }
  ans = (ans * ifac[S - 1]) % MOD;
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
