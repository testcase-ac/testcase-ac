#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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

const int MAXN = 5e5, MOD = 1e9 + 7;
ll A[MAXN + 1], fac[MAXN + 1], ifac[MAXN + 1];

void solve() {
  int N; cin >> N;

  ll sum = 0;
  for (int i = 1; i <= N; ++i) cin >> A[i], sum += A[i];

  ll prob = 0, tot = fac[sum];
  for (int i = 1; i <= N; ++i) {
    prob = (prob + A[i] * lpow(sum, MOD - 2, MOD)) % MOD;
    tot = tot * ifac[A[i]] % MOD;
    sum -= A[i];
  }
  cout << (prob * tot % MOD) << '\n';
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
