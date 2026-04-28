#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const double EPS = 0.0000000001;

bool isEqual(double d1, double d2) {
  return abs(d1 - d2) <= EPS;
}

bool isBetween(double p, double x1, double x2) {
  return min(x1, x2) - EPS <= p && p <= max(x1, x2) + EPS;
}

int main() {
  fast_io();

  double x1, x2, x3, x4, y1, y2, y3, y4;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

  if (isEqual(x1, x2)) {
    if (isEqual(x3, x4)) {
      // No three points are on a straight line, thus x1 != x3
      cout << 0;
    }
    else {
      double a2 = (y4 - y3) / (x4 - x3);
      double yp = a2 * (x1 - x3) + y3;
      cout << (isBetween(x1, x3, x4) && isBetween(yp, y1, y2) && isBetween(yp, y3, y4));
    }
  }
  else {
    if (isEqual(x3, x4)) {
      double a1 = (y2 - y1) / (x2 - x1);
      double yp = a1 * (x3 - x1) + y1;
      cout << (isBetween(x3, x1, x2) && isBetween(yp, y1, y2) && isBetween(yp, y3, y4));
    }
    else {
      double a1 = (y2 - y1) / (x2 - x1);
      double a2 = (y4 - y3) / (x4 - x3);
      if (isEqual(a1, a2)) cout << 0;
      else {
        double xp = (a1 * x1 - a2 * x3 + y3 - y1) / (a1 - a2);
        double yp = a1 * (xp - x1) + y1;
        cout << (
          isBetween(xp, x1, x2) && isBetween(xp, x3, x4) &&
          isBetween(yp, y1, y2) && isBetween(yp, y3, y4)
        );
      }
    }
  }
}
