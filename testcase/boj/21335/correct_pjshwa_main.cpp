#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll a;
  cin >> a;

  double r = sqrt(a / M_PI);
  cout << fixed << setprecision(10) << 2 * M_PI * r << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
