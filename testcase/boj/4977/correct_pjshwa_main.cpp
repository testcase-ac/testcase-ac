#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ld S;
ld f(ld r) {
  return expl(-r * r / (2 * S * S));
}

void solve() {
  ld r[6];
  for (int i = 0; i < 6; ++i) cin >> r[i];
  cin >> S;

  ld ans = 0;
  ans += (f(0) - f(r[0])) * 50;
  ans += (f(r[0]) - f(r[1])) * 25;
  ans += (f(r[1]) - f(r[2])) * 10.5;
  ans += (f(r[2]) - f(r[3])) * 31.5;
  ans += (f(r[3]) - f(r[4])) * 10.5;
  ans += (f(r[4]) - f(r[5])) * 21.0;

  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
