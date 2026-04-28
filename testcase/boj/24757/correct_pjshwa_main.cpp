#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3300;
double d[MAX + 10][MAX + 10];

void solve() {
  int dl, dw, g, l;
  cin >> dl >> dw >> g >> l;

  d[0][0] = 1;
  for (int trial = 0; trial <= MAX; trial++) for (int lost = 0; lost <= trial; lost++) {
    int fail = trial - lost;
    double P = min(100, lost * dl + fail * dw) / 100.0;

    d[lost + 1][trial + 1] += d[lost][trial] * (l / 100.0);
    d[lost][trial + 1] += d[lost][trial] * ((100 - l) / 100.0) * (1 - P);
  }

  double ans = 0;
  for (int trial = 0; trial <= MAX; trial++) for (int lost = 0; lost <= trial; lost++) {
    int fail = trial - lost;
    double P = min(100, lost * dl + fail * dw) / 100.0;

    ans += (trial + 1) * d[lost][trial] * ((100 - l) / 100.0) * P;
  }

  ans = (ans * 100 / g);
  cout << fixed << setprecision(12) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
