#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7, INV2 = 5e8 + 4;

void solve() {
  ll N, M; string X; cin >> N >> M >> X;
  reverse(X.begin(), X.end());

  ll ans = 0, w = 1;
  if (N == 1) {
    for (int i = 0; i < M; ++i) {
      ll cur = (X[i] - '0') * w % MOD;
      ans = (ans + cur) % MOD;
      w = w * 2 % MOD;
    }
  }
  else {
    N %= MOD;
    for (int i = 0; i < M; ++i) {
      ll cur = N * INV2 % MOD;
      cur = cur * w % MOD;
      ans = (ans + cur) % MOD;
      w = w * 2 % MOD;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
