#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  double L = 0, R, P[3][2]; cin >> R;
  for (int i = 0; i < 3; ++i) cin >> P[i][0] >> P[i][1];

  for (int i = 0; i < 3; ++i) {
    double i1 = P[i][0], i2 = P[i][1];
    if (i1 == i2) continue;

    double m = (i1 + i2) / 2;
    double M = (L + R) / 2;
    if (m <= M) {
      L = m;
      for (int j = i + 1; j < 3; ++j) {
        if (P[j][0] <= m) P[j][0] = m + (m - P[j][0]);
        if (P[j][1] <= m) P[j][1] = m + (m - P[j][1]);
      }
    } else {
      R = m;
      for (int j = i + 1; j < 3; ++j) {
        if (P[j][0] >= m) P[j][0] = m - (P[j][0] - m);
        if (P[j][1] >= m) P[j][1] = m - (P[j][1] - m);
      }
    }

    // cout << "P = ";
    // for (int i = 0; i < 3; ++i) cout << P[i][0] << ' ' << P[i][1] << "   ";
    // cout << '\n';

    // cout << "L = " << L << "   R = " << R << '\n';
  }

  cout << fixed << setprecision(1) << R - L << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
