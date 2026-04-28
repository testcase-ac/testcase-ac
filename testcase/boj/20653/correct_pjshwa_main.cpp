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
  int n, g, l;
  cin >> n >> g >> l;
  if (l % g) return cout << "0\n", void();

  l /= g;
  int ol = l;
  ll ans = 1;
  for (int p = 2; p * p <= ol; p++) {
    int cnt = 0;
    while (l % p == 0) {
      l /= p;
      cnt++;
    }
    if (cnt == 0) continue;

    ll cur = 0;
    cur = (cur + lpow(cnt + 1, n, MOD)) % MOD;
    cur = (cur + lpow(cnt - 1, n, MOD)) % MOD;
    cur = (cur + MOD - lpow(cnt, n, MOD)) % MOD;
    cur = (cur + MOD - lpow(cnt, n, MOD)) % MOD;
    ans = (ans * cur) % MOD;
  }
  if (l > 1) {
    ll cur = 0;
    cur = (cur + lpow(2, n, MOD)) % MOD;
    cur = (cur + MOD - 2) % MOD;
    ans = (ans * cur) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
