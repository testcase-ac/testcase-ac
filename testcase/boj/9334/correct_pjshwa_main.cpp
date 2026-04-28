#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

double eps = 1e-4;
double ans(vector<double>& a) {
  int n = a.size();
  bool able;
  double a1, a2, a3, det;

  // d = 1
  able = true;
  a1 = a[1] / a[0];
  for (int i = 1; i < n; i++) {
    if (abs(a[i] - a1 * a[i - 1]) > eps) able = false;
  }
  if (able) return a[n - 1] * a1;

  // d = 2
  able = true;
  det = a[1] * a[1] - a[0] * a[2];
  a1 = (a[1] * a[2] - a[0] * a[3]) / det;
  a2 = (a[1] * a[3] - a[2] * a[2]) / det;
  for (int i = 2; i < n; i++) {
    if (abs(a[i] - a[i - 1] * a1 - a[i - 2] * a2) > eps) able = false;
  }
  if (able) return a[n - 1] * a1 + a[n - 2] * a2;

  // d = 3
  able = true;
  det = a[2] * a[2] * a[2] + a[1] * a[1] * a[4] + a[3] * a[3] * a[0] - a[4] * a[2] * a[0] - 2 * a[1] * a[2] * a[3];
  a1 = (a[3] * (a[2] * a[2] - a[1] * a[3]) + a[4] * (a[3] * a[0] - a[1] * a[2]) + a[5] * (a[1] * a[1] - a[0] * a[2])) / det;
  a2 = (a[3] * (a[1] * a[4] - a[2] * a[3]) + a[4] * (a[2] * a[2] - a[0] * a[4]) + a[5] * (a[0] * a[3] - a[1] * a[2])) / det;
  a3 = (a[3] * (a[3] * a[3] - a[2] * a[4]) + a[4] * (a[1] * a[4] - a[3] * a[2]) + a[5] * (a[2] * a[2] - a[1] * a[3])) / det;
  return a[n - 1] * a1 + a[n - 2] * a2 + a[n - 3] * a3;
}

int main() {
  fast_io();

  int t, n;
  cin >> t;

  vector<double> a;
  while (t--) {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << (int)round(ans(a)) << '\n';
  }
}
