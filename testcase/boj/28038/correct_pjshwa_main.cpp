#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int op; cin >> op;
  if (op == 1) {
    ld x, y; cin >> x >> y;

    ld r = sqrt(x * x + y * y);
    ld theta = atan2(y, x);

    cout << fixed << setprecision(16) << r << ' ' << theta << '\n';
  }
  else {
    ld r, theta; cin >> r >> theta;

    ld x = r * cos(theta);
    ld y = r * sin(theta);

    cout << fixed << setprecision(16) << x << ' ' << y << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
