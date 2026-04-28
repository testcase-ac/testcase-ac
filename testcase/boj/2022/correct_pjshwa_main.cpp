#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
int main() {
  double x, y, c;
  cin >> x >> y >> c;

  double left = 0.0, right = min(x, y);
  double mid = (left + right) / 2;

  while (right - left > eps) {
    double cx = sqrt(x * x - mid * mid), cy = sqrt(y * y - mid * mid);
    if (cx * cy / (cx + cy) > c) left = mid + eps;
    else right = mid;

    mid = (left + right) / 2;
  }

  cout << fixed << setprecision(12) << mid;
}
