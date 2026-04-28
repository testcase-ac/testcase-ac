#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;
  set<pii> s;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    s.insert({2 * x, 2 * y});
  }

  int ans = 0;
  for (auto& [x1, y1] : s) for (auto& [x2, y2] : s) {
    if (x1 == x2 && y1 == y2) continue;

    int xc = (x1 + x2) / 2, yc = (y1 + y2) / 2;
    int xd = (x1 - x2) / 2, yd = (y1 - y2) / 2;

    int x3 = xc - yd, y3 = yc + xd;
    int x4 = xc + yd, y4 = yc - xd;

    if (s.count({x3, y3}) && s.count({x4, y4})) ans++;
  }

  cout << ans / 4 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
