#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int x, y, a, b;
  cin >> x >> y >> a >> b;
  y -= x;

  if (y % (a + b) == 0) cout << y / (a + b) << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
