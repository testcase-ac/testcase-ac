#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 998244353;

void solve() {
  string S;
  cin >> S;

  ll m = 1;
  for (int i = 0; i < S.size() - 1; i++) m = (m * 2) % MOD;

  ll r = 1, ans = 0;
  for (int i = S.size() - 1; i >= 0; i--) {
    ll v = S[i] - '0';
    v = (v * r) % MOD;
    v = (v * m) % MOD;
    ans = (ans + v) % MOD;

    m = (m * 499122177) % MOD;
    r = (r * 11) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
