#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll ccw(pll a, pll b, pll c) {
  ll u = (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
  if (u > 0) return 1;
  else if (u == 0) return 0;
  else return -1;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Segment {
  pll x, y;
};

bool intersects(Segment x, Segment y) {
  ll abc = ccw(x.x, x.y, y.x), abd = ccw(x.x, x.y, y.y);
  ll cda = ccw(y.x, y.y, x.x), cdb = ccw(y.x, y.y, x.y);
  if (abc * abd == 0 && cda * cdb == 0) {
    if (x.x > x.y) swap(x.x, x.y);
    if (y.x > y.y) swap(y.x, y.y);
    return x.x <= y.y && y.x <= x.y;
  }
  else return abc * abd <= 0 && cda * cdb <= 0;
}

void solve() {
  int x1, y1, x2, y2, x3, y3, x4, y4;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
  Segment x = {pll{x1, y1}, pll{x2, y2}};
  Segment y = {pll{x3, y3}, pll{x4, y4}};
  cout << intersects(x, y) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
