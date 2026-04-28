#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

void solve() {
  int R, C;
  cin >> R >> C;

  ll ans = 1;
  for (int i = R + 1; i <= R * C; i++) ans = (ans * i) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
