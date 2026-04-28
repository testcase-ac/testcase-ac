#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  double s, r;
  cin >> s >> r;

  double res;
  if (2 * r < s) res = r * r * M_PI;
  else if (sqrt(2) * r > s) res = s * s;
  else {
    double a = s / 2;
    double th = acos(a / r);
    res = r * r * (M_PI - 4 * th) + 4 * a * r * sin(th);
  }

  cout << fixed << setprecision(2) << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
