#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MOD = 1e7 - 9;
int A[MAXN];
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
  if (n < 0 || k < 0) return 0;
  return C(n + k - 1, k);
}

ll rec(int l, int r) {
  if (l >= r) return 1;

  ll ret = fac[r - l]; vector<int> gt, lt;
  for (int i = l + 1; i <= r; i++) {
    if (A[i] > A[l]) gt.push_back(A[i]);
    else lt.push_back(A[i]);
  }
  ret = ret * ifac[gt.size()] % MOD;
  ret = ret * ifac[lt.size()] % MOD;

  int i = l + 1, fg;
  for (int e : lt) A[i++] = e;
  fg = i;
  for (int e : gt) A[i++] = e;

  ret = ret * rec(l + 1, fg - 1) % MOD;
  ret = ret * rec(fg, r) % MOD;
  return ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  cout << rec(0, N - 1) << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAXN] = lpow(fac[MAXN], MOD - 2, MOD);
  for (int i = MAXN - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
