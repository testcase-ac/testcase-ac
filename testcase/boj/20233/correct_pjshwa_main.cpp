#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a, x, b, y, T;
  cin >> a >> x >> b >> y >> T;

  cout << a + 21 * max(0, T - 30) * x << ' ' << b + 21 * max(0, T - 45) * y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
