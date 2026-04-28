#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
double t;

double f(int x) {
  double prize = 1 << (n - x);
  if (x == 0) return prize;

  double prev_exp = f(x - 1), ans = 0;
  double thresh = prize / prev_exp;
  ans += max(0.0, thresh - t) * prize;

  double l = max(thresh, t);
  ans += 0.5 * prev_exp * (1 - l * l);

  return ans / (1 - t);
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> t;
    if (n == 0 && t == 0.0) break;

    cout << fixed << setprecision(3) << f(n) << '\n';
  }
}
