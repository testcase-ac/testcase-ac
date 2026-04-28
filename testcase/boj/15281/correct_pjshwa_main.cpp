#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const double INF = 1e18;

struct Point {
  double x, y;
  Point operator+(const Point& p) const {
    return {x + p.x, y + p.y};
  }
  Point operator-(const Point& p) const {
    return {x - p.x, y - p.y};
  }
  Point operator*(double c) const {
    return {x * c, y * c};
  }
  double operator*(const Point& p) const {
    return x * p.x + y * p.y;
  }
  double norm() const {
    return sqrt(x * x + y * y);
  }
};

// solves norm(x - y + t * v) = 2r, where t >= 0
double f(Point& x, Point& y, Point& v, double r) {
  Point d = x - y;
  double a = v * v;
  double b = 2 * (d * v);
  double c = d * d - 4 * r * r;
  double det = b * b - 4 * a * c;
  if (det < 0) return INF;

  double t1 = (-b + sqrt(det)) / (2 * a);
  double t2 = (-b - sqrt(det)) / (2 * a);
  if (t1 < 0) {
    if (t2 < 0) return INF;
    return t2;
  }
  else if (t2 < 0) return t1;
  else return min(t1, t2);
}

void solve() {
  Point P[3];
  for (int i = 0; i < 3; ++i) {
    double x, y; cin >> x >> y;
    P[i] = {x, y};
  }
  double xv, yv, r; cin >> xv >> yv >> r;
  Point V = {xv, yv};

  double t1 = f(P[0], P[1], V, r);
  double t2 = f(P[0], P[2], V, r);

  if (t1 == INF && t2 == INF) return cout << "5\n", void();
  if (t1 != INF && t2 != INF) {
    if (t1 < t2) t2 = INF;
    else t1 = INF;
  }

  if (t1 == INF) {
    Point nX = P[0] + V * t2;
    Point nV = P[2] - nX;
    if (f(nX, P[1], nV, r) == INF) cout << "4\n";
    else cout << "2\n";
  }
  else {
    Point nX = P[0] + V * t1;
    Point nV = P[1] - nX;
    if (f(nX, P[2], nV, r) == INF) cout << "3\n";
    else cout << "1\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
