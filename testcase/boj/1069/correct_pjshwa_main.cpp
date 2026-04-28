#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  double X, Y, D, T; cin >> X >> Y >> D >> T;
  double dist = sqrt(X * X + Y * Y);

  double U = floor(dist / D), ans = dist;
  if (U == 0) {
    ans = min(ans, T * 2);
    ans = min(ans, T + D - dist);
  } else {
    ans = min(ans, U * T + dist - U * D);
    ans = min(ans, (U + 1) * T);
  }
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
