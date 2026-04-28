#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll A, B, C, D;
  cin >> A >> B >> C >> D;

  ll ans = 0;
  for (int n = 1; n < 1000; n++) {
    for (int d = 1; d < 1000; d++) {
      if (__gcd(n, d) > 1) continue;
      if (n + d >= 1000) break;

      ll start = max((A - 1) / n + 1, (C - 1) / d + 1);
      ll end = min(B / n, D / d);

      if (start > end) continue;
      ans += (end - start + 1);
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
