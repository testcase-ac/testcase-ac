#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  deque<pair<double, double>> q, nq;
  for (int i = 0; i < N; ++i) {
    double x; cin >> x;
    q.emplace_back(x, 1);
  }

  while (q.size() > 1) {
    int z = q.size();
    for (int i = 0; i < z - 1; ++i) {
      auto [ax, ay] = q[i]; auto [bx, by] = q[i + 1];
      double q = (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
      double d = 0.5 * sqrt(16 - q);

      double nx, ny;
      if (ay == by) nx = (ax + bx) / 2, ny = ay + d;
      else {
        double cx = (ax + bx) / 2, cy = (ay + by) / 2;
        double m = (by - ay) / (bx - ax);
        m = -1 / m;

        double xd = d / sqrt(1 + m * m), yd = m * xd;
        if (yd < 0) xd = -xd, yd = -yd;
        nx = cx + xd, ny = cy + yd;
      }
      nq.emplace_back(nx, ny);
    }
    q = move(nq);
  }

  auto [x, y] = q[0];
  cout << fixed << setprecision(4) << x << ' ' << y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
