#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  int n, m; cin >> n >> m;

  ll ans = 0;
  for (int s = 0; s < (1 << n); s++) {
    int max_alt_streak = 1, alt_streak = 1, l = s & 1;
    for (int i = 1; i < n; i++) {
      if (l == (s >> i & 1)) {
        max_alt_streak = max(max_alt_streak, alt_streak);
        alt_streak = 1;
      }
      else {
        l = s >> i & 1;
        alt_streak++;
      }
    }
    max_alt_streak = max(max_alt_streak, alt_streak);

    if (max_alt_streak == m) {
      ll cur = 1;
      for (int i = 0; i < n; i++) {
        int x = s >> i & 1;
        if (x) cur = (cur * 5) % MOD;
        else cur = (cur * 11) % MOD;
      }
      ans = (ans + cur) % MOD;
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
