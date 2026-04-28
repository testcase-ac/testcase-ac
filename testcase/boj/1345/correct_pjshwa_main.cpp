#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const long double EPS = 1e-12;
int a[50];
int main() {
  fast_io();

  int n, a0;
  cin >> n >> a0;
  for (int i = 0; i < n; i++) cin >> a[i];

  if (n == 0) return cout << 0, 0;
  if (a[0] < a0) return cout << -1, 0;

  long double left = a[0] - a0, right = left + 1;
  long double mid = (left + right) / 2;
  bool able;

  int it = 400;
  while (it--) {
    able = true;
    for (int i = 0; i < n; i++) if (floor(a0 + mid * (i + 1)) < a[i]) able = false;

    if (able) right = mid;
    else left = mid + EPS;

    mid = (left + right) / 2;
  }

  able = true;
  long double ai = a0;
  for (int i = 0; i < n; i++) {
    ai += mid;
    if (floor(ai) != a[i]) able = false;
  }

  if (able) cout << fixed << setprecision(10) << mid;
  else cout << -1;
}
