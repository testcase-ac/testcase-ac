#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, p;
  cin >> n >> p;
  int lmax = n / (p - 1);
  double res = (double)(lmax * p) / (n + 1);
  for (int i = 2; i <= lmax; ++i) res *= (double)(n - p + i) / (n + i);
  cout << fixed << setprecision(7) << res << '\n';
}
