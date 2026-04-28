#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int ccw(pll a, pll b, pll c) {
  ll u = (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
  if (u > 0) return 1;
  else if (u == 0) return 0;
  else return -1;
}

void solve() {
  int x1, y1, x2, y2, x3, y3, x4, y4;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
  cout << (ccw({x1, y1}, {x2, y2}, {x3, y3}) * ccw({x1, y1}, {x2, y2}, {x4, y4}) < 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
