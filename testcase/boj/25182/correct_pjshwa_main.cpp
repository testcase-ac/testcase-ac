#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;

void solve() {
  int n;
  cin >> n;

  ll fac = 1, sum = 0;
  for (int i = 1; i <= n; i++) {
    fac = (fac * i) % MOD;
    sum = (sum + i) % MOD;
  }

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ll cur = (sum + i) * i % MOD;
    ans = (ans + cur) % MOD;
  }

  cout << ans << ' ' << (fac * fac) % MOD << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
