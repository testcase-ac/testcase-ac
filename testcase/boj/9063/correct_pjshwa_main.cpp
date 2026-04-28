#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  int xl = INF, yl = INF, xr = -INF, yr = -INF;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    xl = min(xl, x);
    yl = min(yl, y);
    xr = max(xr, x);
    yr = max(yr, y);
  }
  cout << (xr - xl) * (yr - yl) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
