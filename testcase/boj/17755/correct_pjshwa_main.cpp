#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll k, a, b, ans = 0; cin >> k >> a >> b;
  for (int s = 1; s <= 1458; s++) {
    ll u = k * s;
    if (u > b) break;
    if (u < a) continue;

    int sum_sq = 0;
    for (char c : to_string(u)) {
      int d = c - '0';
      sum_sq += d * d;
    }
    if (sum_sq == s) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
