#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;

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
  
  ll c = 1, a = 1;
  for (int i = 1; i <= n; i++) {
    c = (c * (n + i)) % MOD;
    a = (a * i) % MOD;
  }
  c = (c * lpow(a, MOD - 2, MOD)) % MOD;
  cout << c << ' ' << n * n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
