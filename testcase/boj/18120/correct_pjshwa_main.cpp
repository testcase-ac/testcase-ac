#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100'000;
pair<double, tuple<int, int, int>> grains[MAX + 1];
int wss[MAX + 1];
double pss[MAX + 1];
int main() {
  fast_io();

  int n, a;
  cin >> n >> a;

  int xi, yi, wi, ws = 0;
  double di, s = 0;
  for (int i = 1; i <= n; i++) {
    cin >> xi >> yi >> wi;
    di = sqrt(xi * xi + yi * yi);
    grains[i] = {di, {xi, yi, wi}};
  }
  sort(grains + 1, grains + n + 1);

  double r, mr = 0;
  grains[0].first = 0;

  for (int i = 1; i <= n; i++) {
    di = grains[i].first;
    tie(xi, yi, wi) = grains[i].second;

    wss[i] = wi;
    pss[i] = di * wi;
    wss[i] += wss[i - 1];
    pss[i] += pss[i - 1];

    r = wss[i];
    r /= (2 * a);

    if (r >= di && (i == n || r <= grains[i + 1].first)) mr = max(mr, wss[i] * r - pss[i] - r * r * a);
  }

  cout << fixed << setprecision(12) << mr;
}
