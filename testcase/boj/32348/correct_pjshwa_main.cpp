#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, MOD = 1e9 + 7;
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

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

ll H(int n, int k) {
  return C(n + k - 1, k);
}

void solve() {
  int N, M; cin >> N >> M;
  vector<int> A(N), B(M);
  for (int &x : A) cin >> x;
  for (int &x : B) cin >> x;
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  reverse(B.begin(), B.end());
  
  int maxl = 2e9 + 1;
  for (int i = 0; i < N; ++i) maxl = min(maxl, A[i] + (i < M ? B[i] : 0));

  ll i = 0, j = 0, ans = 1, ocnt = 0;
  for (int i = 0; i < N; ++i) ocnt += A[i] >= maxl;
  for (i = 0; i < N; ++i) {
    if (A[i] >= maxl) break;
    while (j < M && A[i] + B[j] >= maxl) ++j;
    ans = ans * (j - i) % MOD;
  }
  ll u = 0;
  for (int l = 0; l <= M - i; ++l) {
    ll e = C(ocnt, l);
    e = e * fac[M - i] % MOD;
    e = e * ifac[M - i - l] % MOD;
    u = (u + e) % MOD;
  }
  ans = ans * u % MOD;
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
