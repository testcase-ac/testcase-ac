#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int w, h; double r; cin >> w >> h >> r;
  double ans = w * h - r * r * acos(-1.0) / 4;
  cout << fixed << setprecision(6) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
