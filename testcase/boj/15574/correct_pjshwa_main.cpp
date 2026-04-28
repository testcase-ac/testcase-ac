#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

double euc(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  fast_io();

  int n;
  cin >> n;
  set<int> xs;
  unordered_map<int, int> ymin, ymax;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    xs.insert(x);
    if (ymin.count(x)) ymin[x] = min(ymin[x], y);
    else ymin[x] = y;
    if (ymax.count(x)) ymax[x] = max(ymax[x], y);
    else ymax[x] = y;
  }

  int cnt = 0;
  int px, pminy, pmaxy;
  double yd1 = 0, yd2 = 0;
  for (int x : xs) {
    cnt++;
    if (cnt == 1) {
      px = x, pminy = ymin[x], pmaxy = ymax[x];
      continue;
    }

    double cd1 = max(
      yd1 + euc(px, pminy, x, ymin[x]),
      yd2 + euc(px, pmaxy, x, ymin[x])
    );
    double cd2 = max(
      yd1 + euc(px, pminy, x, ymax[x]),
      yd2 + euc(px, pmaxy, x, ymax[x])
    );

    px = x, pminy = ymin[x], pmaxy = ymax[x];
    yd1 = cd1, yd2 = cd2;
  }

  cout << fixed << setprecision(8) << max(yd1, yd2) << '\n';
}
