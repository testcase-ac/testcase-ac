#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int it, w;
  cin >> it >> w;

  long double dgd, dbd;
  if (w == 0) dgd = 1, dbd = 0;
  else dgd = 0, dbd = 1;

  long double g2g, g2b, b2g, b2b;
  cin >> g2g >> g2b >> b2g >> b2b;

  while (it--) {
    long double dgd_temp = g2g * dgd + b2g * dbd;
    dbd = g2b * dgd + b2b * dbd;
    dgd = dgd_temp;
  }

  cout << round(1000 * dgd) << '\n' << round(1000 * dbd) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
