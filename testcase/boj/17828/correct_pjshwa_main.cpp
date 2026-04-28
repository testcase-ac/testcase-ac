#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, x;
  cin >> n >> x;

  if (x < n || x > 26 * n) return cout << "!\n", void();
  for (int i = 1; i <= n; i++) {
    int d = max(1, x - 26 * (n - i));
    cout << (char)('A' + d - 1);
    x -= d;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
