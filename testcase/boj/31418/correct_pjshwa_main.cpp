#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

void solve() {
  int W, H, K, T; cin >> W >> H >> K >> T;

  ll ans = 1;
  while (K--) {
    int x, y; cin >> x >> y;
    ll ru = min(W, x + T), rd = max(1, x - T);
    ll cu = min(H, y + T), cd = max(1, y - T);
    ll cur = (ru - rd + 1) * (cu - cd + 1) % MOD;
    ans = (ans * cur) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
