#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

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

void solve() {
  int N; cin >> N;

  vector<Point> hull;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    hull.push_back(Point(x, y));
  }
  swap(hull[0], *min_element(hull.begin(), hull.end()));
  sort(hull.begin() + 1, hull.end(), [&](Point &a, Point &b) {
    ll cw = ccw(hull[0], a, b);
    if (cw != 0) return cw > 0;
    return dist(hull[0], a) < dist(hull[0], b);
  });

  ll total = 0;
  for (int i = 1; i < N - 1; ++i) total += ccw(hull[0], hull[i], hull[i + 1]);

  ll ans = 1e18;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    ll area = 0;
    for (int k = i + 1; k < j; ++k) area += ccw(hull[i], hull[k], hull[k + 1]);
    ans = min(ans, abs(total - 2 * area));
  }
  cout << ans / 2 << '.' << (ans & 1 ? '5' : '0') << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
