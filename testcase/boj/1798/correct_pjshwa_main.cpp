#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  double r, h, d1, a1, d2, a2, an, da, db, dg, ans;
  while (cin >> r >> h >> d1 >> a1 >> d2 >> a2) {
    an = r / sqrt(r * r + h * h);
    da = abs(a2 - a1);
    db = 360 - da;
    dg = min(da, db) * an;
    ans = sqrt(d1 * d1 + d2 * d2 - 2 * d1 * d2 * cos(dg * 3.141591 / 180));

    cout << fixed << setprecision(2) << ans << '\n';
  }
}
