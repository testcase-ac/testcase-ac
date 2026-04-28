#include <bits/stdc++.h>
using namespace std;

int main() {
  int xs, ys, xe, ye, dx, dy;
  cin >> xs >> ys >> xe >> ye >> dx >> dy;

  if (dx == 0 && dy == 0) {
    // no-op
  }
  else if (dx == 0) dy = dy / abs(dy);
  else if (dy == 0) dx = dx / abs(dx);
  else {
    int g = __gcd(abs(dx), abs(dy));
    dx /= g;
    dy /= g;
  }

  int nd, d = (xs - xe) * (xs - xe) + (ys - ye) * (ys - ye);
  while (1) {
    nd = (xs - xe - dx) * (xs - xe - dx) + (ys - ye - dy) * (ys - ye - dy);
    if (nd >= d) {
      cout << xe << ' ' << ye << '\n';
      break;
    }
    d = nd;
    xe += dx;
    ye += dy;
  }
}
