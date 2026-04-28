#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q;
  cin >> Q;
  while (Q--) {
    int x, y, k;
    cin >> x >> y >> k;

    int g = 0;
    while (k--) {
      int l; cin >> l;
      g = __gcd(g, l);
    }

    if (x % g == 0 && y % g == 0) cout << "Ta-da\n";
    else cout << "Gave up\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
