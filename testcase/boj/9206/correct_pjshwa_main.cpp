#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const double PI = 3.141592653589793238;

double f(double a, double b, double h, double x) {
  double fx = a * exp(-x * x) + b * sqrt(x);
  return fx * fx * PI;
}

int main() {
  fast_io();

  double v, a, b, h;
  int n;

  cin >> v >> n;

  double min_diff = 1e18;
  int min_diff_idx = -1;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> h;

    double vol = 0, dx = 1e-4;
    double fa = f(a, b, h, 0);

    // https://ko.wikipedia.org/wiki/%EC%8B%AC%ED%94%84%EC%8A%A8_%EA%B3%B5%EC%8B%9D
    // Riemann Sum 으로 구할 경우 dx 를 훨씬 더 작게 잡아야 함 -> TLE
    // Trapezoidal rule, Simpson's rule 등을 사용하여 더 큰 dx 로 근사를 더 잘 할 수 있는 듯 하다
    for (double j = 0; j < h / dx; j++) {
      double xa = j * dx;
      double xab = xa + dx / 2;
      double xb = xa + dx;
      double fab = f(a, b, h, xab);
      double fb = f(a, b, h, xb);
      double cur_v = (fa + 4 * fab + fb) / 6;
      vol += cur_v * dx;

      fa = fb;
    }

    if (abs(v - vol) < min_diff) {
      min_diff = abs(v - vol);
      min_diff_idx = i;
    }
  }

  cout << min_diff_idx << '\n';
}
