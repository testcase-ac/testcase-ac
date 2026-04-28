#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, c;
  long double j, x = 0, y = 0;
  cin >> n >> x;
  for (int i = 1; i < n; i++) {
    cin >> j;
    y += j;
  }
  cin >> j >> c;

  while (c--) {
    auto tx = x, ty = y;
    x = tx + tx * j / (tx + ty);
    y = ty + ty * j / (tx + ty);
  }

  cout << fixed << setprecision(12) << x << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
