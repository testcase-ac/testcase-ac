#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int W, H, x, y, x1, y1, x2, y2; cin >> W >> H >> x >> y >> x1 >> y1 >> x2 >> y2;
  if (y < y1) cout << "0.0\n";
  else {
    double xd1 = x - x1, xd2 = x - x2, yd = y - y1;
    double xl1 = x1 - xd1 * y1 / yd, xl2 = x2 - xd2 * y2 / yd;
    xl1 = min(1.0 * W, max(0.0, xl1));
    xl2 = min(1.0 * W, max(0.0, xl2));
    assert(xl1 <= xl2);
    cout << fixed << setprecision(10) << (xl2 - xl1) / W << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
