#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

double dist(pii a, pii b) {
  double res = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
  return sqrt(res);
}

pii coords[17];
double d[1 << 17][17];
double w[17][17];
const double MAX = 1e12;
int main() {
  fast_io();

  int n, x, y;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    coords[i] = {x, y};
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) w[i][j] = dist(coords[i], coords[j]);
  }

  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) d[i][j] = MAX;
  }

  d[1][0] = 0;
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        for (int k = 0; k < n; k++) {
          if (
            k != j &&
            !(i & (1 << k)) &&
            w[j][k] > 0
          ) d[i | (1 << k)][k] = min(d[i | (1 << k)][k], d[i][j] + w[j][k]);
        }
      }
    }
  }

  double ans = MAX;
  for (int i = 1; i < n; i++) {
    if (w[i][0] > 0) ans = min(ans, d[(1 << n) - 1][i] + w[i][0]);
  }
  cout << fixed << setprecision(12) << ans << '\n';
}
