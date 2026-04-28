#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, m; cin >> n >> m;
  if (n == 1 || m == 1) cout << n * m << '\n';
  else cout << 2 * (n + m) - 4 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
