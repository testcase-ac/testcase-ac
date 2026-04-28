#include <bits/stdc++.h>
#define x first
#define y second
#define pdd pair<double, double>
using namespace std;

int main(){
  int t;
  cin >> t;

  double eps = 0.000001;

  while (t--) {
    pdd a, b, c;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
    
    pdd d = {a.x - (b.y - a.y), a.y + (b.x - a.x)};
    pdd e = {b.x - (b.y - a.y), b.y + (b.x - a.x)};
    // pdd f = {c.x - (a.y - c.y), c.y + (a.x - c.x)};
    pdd g = {a.x - (a.y - c.y), a.y + (a.x - c.x)};
    // pdd h = {c.x - (c.y - b.y), c.y + (c.x - b.x)};
    pdd j = {b.x - (c.y - b.y), b.y + (c.x - b.x)};
    pdd l = {(d.x + g.x) / 2, (d.y + g.y) / 2};
    pdd m = {(e.x + j.x) / 2, (e.y + j.y) / 2};
    // pdd n = {(f.x + h.x) / 2, (f.y + h.y) / 2};

    double s1 = (m.y - b.y) / (m.x - b.x);
    double r1 = s1 * b.x - b.y;
    double s2 = (l.y - a.y) / (l.x - a.x);
    double r2 = s2 * a.x - a.y;
    double ans_x, ans_y;

    if (fabs(m.x - b.x) < eps) {
      ans_x = b.x;
      ans_y = s2 * ans_x - r2;
    }
    else if (fabs(l.x - a.x) < eps) {
      ans_x = a.x;
      ans_y = s1 * ans_x - r1;
    }
    else {
      ans_x = (r2 - r1) / (s2 - s1);
      ans_y = s1 * ans_x - r1;
    }

    // No minus signs for zero-like numbers
    if (fabs(ans_x) < eps) ans_x = fabs(ans_x);
    if (fabs(ans_y) < eps) ans_y = fabs(ans_y);

    cout << fixed << setprecision(4) << ans_x << ' ' << ans_y << '\n';
  }
}
