#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000, MOD = 1e9 + 7;
ll f[MAX + 1], c[MAX + 1];
ll fac[MAX + 1], ifac[MAX + 1];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
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

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i <= n; i++) cin >> c[i];

  for (int x = 0; x <= n; x++) {
    for (int i = 0; i <= n; i++) {
      ll pw = lpow(x, i, MOD);
      f[x] = (f[x] + pw * c[i]) % MOD;
    }
  }

  cout << "GGG<";
  for (int x = 0; x <= n; x++) {
    bool sign = false;
    ll val = 0;
    for (int i = x; i >= 0; i--) {
      ll coef = C(x, i);
      if (sign) coef = MOD - coef;
      val = (val + coef * f[i]) % MOD;

      sign = !sign;
    }

    cout << val;
    if (x < n) cout << ",";
  }
  cout << ">\n";
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
