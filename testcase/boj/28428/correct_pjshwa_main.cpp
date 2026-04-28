#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int sx, sy, mx, my; cin >> sx >> sy >> mx >> my;
  if (mx == my) {
    if (sx == sy) cout << "YES\n";
    else cout << "NO\n";
  }
  else if (mx > my) {
    if (sx > sy) cout << "YES\n";
    else cout << "NO\n";
  }
  else {
    if (sx < sy) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
