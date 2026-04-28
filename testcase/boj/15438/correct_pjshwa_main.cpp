#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const double EPS = 1e-8;

void solve() {
  int radius, K; cin >> radius >> K;
  vector<tuple<int, int, int, int>> A;
  for (int i = 0; i < K; ++i) {
    int X, Y, R, V; cin >> X >> Y >> R >> V;
    A.emplace_back(X, Y, R, V);
  }

  double l = 0, r = 1e8;
  for (int it = 0; it < 100; ++it) {
    double m = (l + r) / 2;

    vector<pair<double, double>> B; int ok = 0;
    for (auto& [X, Y, R, V] : A) {
      double dist = sqrt((ll)X * X + (ll)Y * Y);
      double reach = (dist - radius) / R;
      if (m < reach) continue;

      double rx = (double)X * radius / dist, ry = (double)Y * radius / dist;
      double th = atan2(ry, rx);
      if (th < 0) th += 2 * M_PI;

      double move = (m - reach) * V;
      if (move >= M_PI * radius) {
        ok = 1;
        break;
      }

      // insert polar coordinates
      double lth = th - move / radius, rth = th + move / radius;
      if (lth < 0) {
        B.emplace_back(lth + 2 * M_PI, 2 * M_PI);
        B.emplace_back(0, rth);
      } else if (rth > 2 * M_PI) {
        B.emplace_back(lth, 2 * M_PI);
        B.emplace_back(0, rth - 2 * M_PI);
      } else {
        B.emplace_back(lth, rth);
      }
    }

    // check whether B covers the circle
    sort(B.begin(), B.end()); double last = 0;
    for (auto& [lth, rth] : B) {
      if (lth > last + EPS) break;
      last = max(last, rth);
    }
    if (last + EPS >= 2 * M_PI) ok = 1;

    if (ok) r = m;
    else l = m;
  }

  cout << fixed << setprecision(10) << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
