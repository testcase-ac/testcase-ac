#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// area of triangle
double area_tri(double x1, double y1, double x2, double y2, double x3, double y3) {
  return abs((x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) / 2);
}

// area of quadrilateral
double area_quad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  return area_tri(x1, y1, x2, y2, x3, y3) + area_tri(x1, y1, x3, y3, x4, y4);
}

void solve() {
  double x[4], y[4];
  for (int i = 0; i < 4; i++) cin >> x[i] >> y[i];

  double total = area_quad(x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);

  // middle points
  double mx[4], my[4];
  for (int i = 0; i < 4; i++) {
    mx[i] = (x[i] + x[(i + 1) % 4]) / 2;
    my[i] = (y[i] + y[(i + 1) % 4]) / 2;
  }

  double dif = min({
    abs(total - 2 * area_tri(x[0], y[0], x[1], y[1], x[2], y[2])),
    abs(total - 2 * area_tri(x[1], y[1], x[2], y[2], x[3], y[3])),
    abs(total - 2 * area_quad(mx[0], my[0], x[1], y[1], x[2], y[2], mx[2], my[2])),
    abs(total - 2 * area_quad(mx[1], my[1], x[2], y[2], x[3], y[3], mx[3], my[3]))
  });

  auto nxt = [&](int i) { return (i + 1) % 4; };
  auto prv = [&](int i) { return (i + 3) % 4; };

  for (int i = 0; i < 4; i++) {
    dif = min({
      dif,
      abs(total - 2 * area_tri(mx[i], my[i], x[nxt(i)], y[nxt(i)], mx[nxt(i)], my[nxt(i)])),
      abs(total - 2 * area_tri(mx[i], my[i], x[nxt(i)], y[nxt(i)], x[nxt(nxt(i))], y[nxt(nxt(i))])),
      abs(total - 2 * area_tri(mx[i], my[i], x[i], y[i], mx[prv(i)], my[prv(i)])),
      abs(total - 2 * area_tri(mx[i], my[i], x[i], y[i], x[prv(i)], y[prv(i)]))
    });
  }

  double a = (total - dif) / 2;
  double b = total - a;
  cout << fixed << setprecision(10) << a << ' ' << b << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
