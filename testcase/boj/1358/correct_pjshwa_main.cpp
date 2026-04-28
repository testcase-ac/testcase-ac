#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int w, h, x, y, p;
  cin >> w >> h >> x >> y >> p;
  int r = h / 2;

  int ans = 0;
  while (p--) {
    int px, py;
    cin >> px >> py;

    if (x <= px && px <= x + w && y <= py && py <= y + h) ans++;
    else if (
      (px - x) * (px - x) + (py - y - r) * (py - y - r) <= r * r ||
      (px - x - w) * (px - x - w) + (py - y - r) * (py - y - r) <= r * r
    ) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
