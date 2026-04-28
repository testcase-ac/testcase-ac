#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  ll N; cin >> N;

  ll ans = 0, inv6 = 166666668;
  for (int r1 = 0; r1 < 50; ++r1) for (int r5 = 0; r5 < 10; ++r5)
  for (int r10 = 0; r10 < 5; ++r10) for (int r25 = 0; r25 < 2; ++r25) {
    ll rt = r1 + 5 * r5 + 10 * r10 + 25 * r25;
    if (N < rt || (N - rt) % 50 != 0) continue;

    // g groups of 50, each group is consisted of either 1, 5, 10, or 25 coins only
    // = 4Hg = (g+3)C3
    ll g = (N - rt) / 50;

    ll cur = 1;
    for (int i = 1; i <= 3; ++i) {
      ll val = (g + i) % MOD;
      cur = cur * val % MOD;
    }
    cur = cur * inv6 % MOD;
    ans = (ans + cur) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
