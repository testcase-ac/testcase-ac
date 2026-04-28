#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, x1, y1, x2, y2, xc, yc; cin >> n >> x1 >> y1 >> x2 >> y2 >> xc >> yc;

  auto move_1 = [&]() {
    if (x1 == xc) {
      if (y1 > yc) --y1;
      else if (y1 < yc) ++y1;
    } else {
      if (x1 > xc) --x1;
      else if (x1 < xc) ++x1;
    }
  };

  auto move_2 = [&]() {
    if (y2 == yc) {
      if (x2 > xc) --x2;
      else if (x2 < xc) ++x2;
    } else {
      if (y2 > yc) --y2;
      else if (y2 < yc) ++y2;
    }
  };

  while (1) {
    move_1(); move_2();
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
    cin >> xc >> yc;
    if (xc == 0 && yc == 0) break;
  }
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
