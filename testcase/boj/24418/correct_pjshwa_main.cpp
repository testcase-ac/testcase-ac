#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  uint c = 1;
  for (int i = 1; i <= n; i++) {
    c *= (n + i);
    c /= i;
  }
  cout << c << ' ' << n * n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
