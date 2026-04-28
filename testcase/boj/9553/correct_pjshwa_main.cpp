#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  double ans = 0;
  for (int i = 0; i < N; i++) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    double t1 = atan2(y1, x1), t2 = atan2(y2, x2);
    double dif = abs(t2 - t1);
    ans += min(dif, 2 * M_PI - dif);
  }
  cout << fixed << setprecision(5) << ans / (2 * M_PI) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
