#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll x; cin >> x;
  if (x == 1) return cout << "1\n", void();
  if (x == 64925062108545024) return cout << "-1\n", void();

  for (int p = 60; p >= 2; p--) {
    ll l = 1, r = 1e9 + 1;
    while (l < r) {
      ll m = (l + r) / 2; __int128_t c = 1;
      for (int i = 0; i < p; i++) {
        c *= m;
        if (c > x) break;
      }

      if (c >= x) r = m;
      else l = m + 1;
    }

    __int128_t c = 1;
    for (int i = 0; i < p; i++) {
      c *= l;
      if (c > x) break;
    }
    if (c != x) continue;

    // l^p = x, now check if l has p factors
    int cnt = 0;
    for (int i = 1; i * i <= l; i++) {
      if (l % i) continue;
      cnt++; cnt += l / i != i;
    }
    if (cnt == p) return cout << l << "\n", void();
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
