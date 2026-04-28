#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const long double EPS = 1e-11;

ll h, a, b, c, va, vb, vc;
bool f(long double sina1) {
  long double sina2 = vb * sina1 / va;
  if (abs(1 - sina2) < EPS) return 0;
  long double sina3 = vc * sina2 / vb;
  if (abs(1 - sina3) < EPS) return 0;

  long double h1 = sina1 * a / sqrt(1 - sina1 * sina1);
  long double h2 = sina2 * b / sqrt(1 - sina2 * sina2);
  long double h3 = sina3 * c / sqrt(1 - sina3 * sina3);

  return h1 + h2 + h3 < h;
}

void solve() {
  cin >> h >> a >> b >> c >> va >> vb >> vc;

  long double left = 0, right = 1;
  while (left + EPS < right) {
    long double mid = (left + right) / 2;
    if (f(mid)) left = mid;
    else right = mid;
  }

  long double sina1 = left;
  long double sina2 = vb * sina1 / va;
  long double sina3 = vc * sina2 / vb;

  long double h1 = sina1 * a / sqrt(1 - sina1 * sina1);
  long double h2 = sina2 * b / sqrt(1 - sina2 * sina2);
  long double h3 = sina3 * c / sqrt(1 - sina3 * sina3);

  long double ans = h1 / sina1 / va + h2 / sina2 / vb + h3 / sina3 / vc;
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
