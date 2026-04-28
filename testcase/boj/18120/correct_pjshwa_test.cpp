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

  double mr;
  for (double r = 0.0; r <= 400; r += 0.1) {
    mr = 0;
    for (int i = 1; i <= n; i++) {
      di = grains[i].first;
      tie(xi, yi, wi) = grains[i].second;
      if (di <= r) mr += (r - di) * wi;
    }
    cout << fixed << setprecision(12) << r << "," << max(0.0, mr - r * r * a) << endl;
  }

}
