#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll L, R, base = 0, mask; cin >> L >> R;
  for (int b = 60; b >= 0; --b) {
    mask = 1LL << b;
    if (R >= mask + base && L < mask + base) {
      base += mask;
      cout << base << ' ' << base - 1 << '\n';
      return;
    } else if (L >= mask + base) base += mask;
  }
  cout << L << ' ' << R << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
