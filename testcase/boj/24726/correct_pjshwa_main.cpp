#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int x1, y1, x2, y2, x3, y3;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

  double centx = (x1 + x2 + x3) / 3.0;
  double centy = (y1 + y2 + y3) / 3.0;
  double area = abs((x1 - x2) * (y2 - y3) - (x2 - x3) * (y1 - y2)) / 2.0;
  cout << fixed << setprecision(10) << area * centy * 2 * M_PI << ' ' << area * centx * 2 * M_PI << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
