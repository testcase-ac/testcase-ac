#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int a, b;
ld f(ld x) {
  return a * x + b * sin(x);
}

int main() {
  int c;
  cin >> a >> b >> c;

  ld left = 0, right = 1e5, mid, eps = 1e-12;
  for (int i = 0; i < 100; i++) {
    mid = (left + right) / 2;
    if (f(mid) < c) left = mid + eps;
    else right = mid;
  }
  cout << fixed << setprecision(10) << mid << '\n';
}
