#include <bits/stdc++.h>
#define ll long long
using namespace std;

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

  // Look at dolls from narrowest to widest
  for (int p = 0; p < n; p++) {
    // Find a tallest shorter doll from the narrower dolls
    if (s.upper_bound(v[p]) != s.end()) {
      // Put it inside this doll
      s.erase(s.upper_bound(v[p]));
      ans--;
    }
    ov.push_back(v[p]);
    // If the next doll is wider, 
    // enter all seen dolls into set of dolls to consider for insertion
    if (p + 1 < n && v[p].x < v[p + 1].x) {
      s.insert(ov.begin(), ov.end());
      ov.clear();
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
