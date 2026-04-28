#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k;
  cin >> n >> k;

  for (int i = 0, x; i < n; i++) {
    cin >> x;
    while (k > 0 && x % 2 == 0) {
      x /= 2;
      k--;
    }
  }

  cout << (k == 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
