#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, xL, yL; cin >> N >> xL >> yL;

  vector<pair<double, double>> segs;
  for (int i = 0; i < N; ++i) {
    double x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    double r1 = y1 / (yL - y1), r2 = y2 / (yL - y2);
    double xg1 = x1 + r1 * (x1 - xL), xg2 = x2 + r2 * (x2 - xL);
    segs.emplace_back(min(xg1, xg2), max(xg1, xg2));
  }
  sort(segs.begin(), segs.end());

  vector<pair<double, double>> segs_m;
  for (auto [l, r] : segs) {
    if (segs_m.empty() || segs_m.back().second < l) segs_m.emplace_back(l, r);
    else segs_m.back().second = max(segs_m.back().second, r);
  }

  cout << segs_m.size() + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
