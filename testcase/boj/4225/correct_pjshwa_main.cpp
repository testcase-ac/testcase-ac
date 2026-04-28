#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
  ll x, y;
  Point(ll a, ll b) : x(a), y(b) {};
  Point() {};
  bool operator<(const Point &rhs) const {
    if (x != rhs.x) return x < rhs.x;
    return y < rhs.y;
  }
};

ll ccw(Point pt1, Point pt2, Point pt3) {
  return (pt1.x * pt2.y + pt2.x * pt3.y + pt3.x * pt1.y) - (pt2.x * pt1.y + pt3.x * pt2.y + pt1.x * pt3.y);
}

ll dist(Point pt1, Point pt2) {
  ll dx = pt2.x - pt1.x;
  ll dy = pt2.y - pt1.y;
  return dx * dx + dy * dy;
}

vector<Point> point;
int main() {
  int n;
  while (1) {
    cin >> n;
    if (!n) break;

    point.resize(n);
    for (int i = 0; i < n; i++) cin >> point[i].x >> point[i].y;

    vector<Point> hull;
    swap(point[0], *min_element(point.begin(), point.end()));
    sort(point.begin() + 1, point.end(), [](Point x, Point y) {
      ll cw = ccw(point[0], x, y);
      if (cw == 0) return dist(point[0], x) < dist(point[0], y);
      return cw > 0;
    });

    for (auto i : point) {
      while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), i) <= 0) hull.pop_back();
      hull.push_back(i);
    }
    int sz = hull.size();

    ll mdist = 1e18;
    for (int i = 0; i < sz; i++) {
      for (int j = i + 1; j < sz; j++) mdist = min(mdist, dist(hull[i], hull[j]));
    }

    cout << sqrt(mdist) << '\n';
  }
}
