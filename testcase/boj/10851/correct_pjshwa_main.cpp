#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// area of triangle
ld area_tri(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3) {
  return abs((x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) / 2);
}

ll ccw(pll a, pll b, pll c) {
  return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

void solve() {
  ld a; int n; cin >> a >> n;
  vector<pii> A(n);
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }

  // area of polygon
  ld total = 0;
  for (int i = 1; i < n - 1; i++) {
    total += ccw(A[0], A[i], A[i + 1]);
  }
  total = abs(total) / 2;

  ld base = total;
  for (int i = 0; i < n; i++) {
    auto& [ax, ay] = A[(i + n - 1) % n];
    auto& [bx, by] = A[i];
    auto& [cx, cy] = A[(i + 1) % n];

    ld mx = (ax + bx) / 2.0;
    ld my = (ay + by) / 2.0;
    ld nx = (bx + cx) / 2.0;
    ld ny = (by + cy) / 2.0;

    base -= area_tri(mx, my, bx, by, nx, ny);
  }

  ld ans = (total - base) / (total * (1 - a));
  ans = 2 * sqrt(ans);
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
