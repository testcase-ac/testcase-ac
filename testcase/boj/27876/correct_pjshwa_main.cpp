#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

void solve() {
  int N; cin >> N;
  if (N == 1) return cout << "1\n", void();
  if (N < 14) return cout << "-1\n", void();

  ll ans = 29030400;
  for (ll i = 15; i <= N; i++) {
    ll q = sqrt(i + i - 1);
    ll d = q * q - i;
    ans = (ans * (i - d)) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
