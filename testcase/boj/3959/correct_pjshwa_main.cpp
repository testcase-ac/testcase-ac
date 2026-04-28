#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const double EPS = 1e-6, g = 9.81;

double p, H, L, v0;
double h(double l) {
  if (l < 0) return H;
  if (l < L / 2) return H * (1 - 2 * (l / L) * (l / L));
  if (l < L) return 2 * H * (l / L - 1) * (l / L - 1);
  return 0;
}

double hp(double l) {
  if (l < 0) return 0;
  if (l < L / 2) return -4 * H * l / (L * L);
  if (l < L) return 4 * H * (l / L - 1) / L;
  return 0;
}

double f(double l) {
  return g / -2 * (l / v0) * (l / v0) + H + p;
}

double fp(double l) {
  return g * l * -1 / (v0 * v0);
}

void solve() {
  double j;
  cin >> j >> p >> H >> L;

  v0 = sqrt(2 * g * j);
  double left = 0, right = 1e4;
  while (left + EPS < right) {
    double mid = (left + right) / 2;
    if (f(mid) > h(mid)) left = mid;
    else right = mid;
  }

  double l = left;
  double vl = sqrt(2 * g * (j + p + H - f(l)));
  double a = 180.0 / M_PI * atan(abs((hp(l) - fp(l)) / (1 + hp(l) * fp(l))));

  cout << fixed << setprecision(7) << l << ' ' << vl << ' ' << a << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
