#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e6, MOD = 1e9 + 7;
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
  int n, k; string s; cin >> n >> k >> s;
  
  int oc = 0;
  for (char c : s) if (c == '1') oc++;
  if (oc % k) return cout << "0\n", void();

  if (oc == 0) return cout << C(n - 1, k - 1) << '\n', void();

  ll ans = 1, run = 0, i = 0;
  while (i < n) {
    if (s[i] == '1') run++;
    if (run == oc / k) {
      int cur = 1;
      while (i < n - 1 && s[i + 1] == '0') cur++, i++;
      if (i < n - 1 && s[i + 1] == '1') ans = (ans * cur) % MOD;
      run = 0;
    }
    i++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
