#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ld a, b, c = 299792458.0;
  cin >> a >> b;
  cout << fixed << setprecision(10) << (a + b) / (1 + a * b / (c * c)) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
