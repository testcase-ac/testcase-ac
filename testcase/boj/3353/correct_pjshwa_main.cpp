#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Point {
  int x, y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}
  bool operator<(const Point& p) const {
    return y > p.y;
  }
};

void solve() {
  int n;
  cin >> n;

  vector<Point> v(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    v[i] = Point(x, y);
  }
  sort(v.begin(), v.end(), [](const Point& a, const Point& b) {return a.x < b.x;});

  multiset<Point> s;
  vector<Point> ov;

  int ans = n;

  for (int p = 0; p < n; p++) {
    if (s.upper_bound(v[p]) != s.end()) {
      s.erase(s.upper_bound(v[p]));
      ans--;
    }
    ov.push_back(v[p]);
    if (p + 1 < n && v[p].x < v[p + 1].x) {
      s.insert(ov.begin(), ov.end());
      ov.clear();
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
