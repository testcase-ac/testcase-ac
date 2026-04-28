#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int upto(int n, int k) {
  if (k == 2) {
    return max(0, n - 2);
  }
  else if (k == 3) {
    return max(0, n / 3 - 1);
  }
  else if (k == 4) {
    if (n < 10) return 0;
    else if (n < 14) return 1;
    else return n / 2 - 5;
  }
  else {
    return max(0, n / 5 - 2);
  }
}

void solve() {
  int l, r, k;
  cin >> l >> r >> k;
  cout << upto(r, k) - upto(l - 1, k) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
