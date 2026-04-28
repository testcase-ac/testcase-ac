#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Point {
  int x, y, z;
  Point() {}
  Point(int x, int y, int z) : x(x), y(y), z(z) {}
};

struct Planet {
  Point center;
  int v, r;
};

const int MAX = 1010;
Planet planets[MAX];
Point points[MAX];

double dist(double x1, double y1, double z1, double x2, double y2, double z2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

double dist(Planet pt, Point p1, Point p2) {
  ll xd = p2.x - p1.x, yd = p2.y - p1.y, zd = p2.z - p1.z;
  ll xu = pt.center.x - p1.x, yu = pt.center.y - p1.y, zu = pt.center.z - p1.z;
  double u = xu * xd + yu * yd + zu * zd;
  u /= (xd * xd + yd * yd + zd * zd);

  if (u < 0) return dist(p1.x, p1.y, p1.z, pt.center.x, pt.center.y, pt.center.z);
  if (u > 1) return dist(p2.x, p2.y, p2.z, pt.center.x, pt.center.y, pt.center.z);
  return dist(p1.x + u * xd, p1.y + u * yd, p1.z + u * zd, pt.center.x, pt.center.y, pt.center.z);
}

void solve() {
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> planets[i].center.x >> planets[i].center.y >> planets[i].center.z >> planets[i].v >> planets[i].r;
  }

  int n;
  cin >> n;
  points[0] = {0, 0, 0};
  for (int i = 1; i <= n; i++) {
    cin >> points[i].x >> points[i].y >> points[i].z;
  }

  int d;
  cin >> d;

  ll ans = 0;
  for (int i = 0; i < m; i++) {
    auto planet = planets[i];
    for (int j = 0; j < n; j++) {
      if (dist(planet, points[j], points[j + 1]) <= d + planet.r) {
        ans += planet.v;
        break;
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
