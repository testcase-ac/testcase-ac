#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
const double EPS = 1e-7;
int a[MAX];
double v[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  double left = 1, right = 1e6;
  while (left + EPS < right) {
    double mid = (left + right) / 2;
    for (int i = 0; i < n; i++) v[i] = a[i] - mid;

    double dt = 0;
    for (int i = 0; i < k; i++) dt += v[i];

    if (dt >= 0) {
      left = mid + EPS;
      continue;
    }

    double pdt = 0, mpdt = 0;
    bool found = false;
    for (int i = k; i < n; i++) {
      dt += v[i];
      pdt += v[i - k];
      mpdt = min(mpdt, pdt);

      if (dt >= mpdt) {
        found = true;
        break;
      }
    }

    if (found) left = mid + EPS;
    else right = mid;
  }

  cout << fixed << setprecision(6) << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
