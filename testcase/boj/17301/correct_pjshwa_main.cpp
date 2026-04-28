#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MOD = 1e9 + 7;
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

void solve() {
  ll N, tot = 0; cin >> N;
  for (int i = 1; i <= N; ++i) tot = (tot + C(N, i) * fac[i]) % MOD;

  int n = 0, c = 0, nc = 0, cn = 0;
  for (int i = 1; i <= N; ++i) {
    string S; cin >> S;
    int Z = S.size(), nf = -1, cl = -1;
    for (int j = 0; j < Z; ++j) {
      if (nf == -1 && S[j] == 'N') nf = j;
      if (S[j] == 'C') cl = j;
    }
    if (nf == -1) ++c;
    else if (cl == -1) ++n;
    else if (nf < cl) ++nc;
    else ++cn;
  }

  // c c ... c (cn) n n ... n
  ll csum = 0, nsum = 0;
  for (int l = 0; l <= N; ++l) {
    csum = (csum + C(c, l) * fac[l]) % MOD;
    nsum = (nsum + C(n, l) * fac[l]) % MOD;
  }

  ll sub = cn + 1;
  sub = sub * csum % MOD;
  sub = sub * nsum % MOD;
  tot = (tot - sub + 1 + MOD) % MOD;
  cout << tot << '\n';
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
