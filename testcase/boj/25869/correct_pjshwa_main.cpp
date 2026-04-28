#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int w, h, d;
  cin >> w >> h >> d;

  if (min(w, h) < 2 * d) cout << "0\n";
  else cout << (w - 2 * d) * (h - 2 * d) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
