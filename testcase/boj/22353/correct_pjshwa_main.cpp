#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

double f[1000], p[1000];
int main() {
  fast_io();

  int a;
  double d, k;
  cin >> a >> d >> k;
  d /= 100; k /= 100;

  f[0] = 1, p[0] = d;
  for (int i = 1; i < 1000; i++) {
    f[i] = f[i - 1] * (1 - p[i - 1]);
    p[i] = min(1.0, p[i - 1] * (1 + k));
  }

  double ans = 0;
  for (int i = 0; i < 1000; i++) ans += f[i] * p[i] * (i + 1);
  cout << fixed << setprecision(12) << ans * a;
}
