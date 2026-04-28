#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int p, q;
  cin >> p >> q;
  for (int i = 1; i <= p; i++) for (int j = 1; j <= q; j++) {
    if (p % i == 0 && q % j == 0) cout << i << ' ' << j << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
