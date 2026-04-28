#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m, p;
  cin >> n >> m >> p;

  int ans = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    if (2 * (i + j) < p) continue;
    ans += (n - i + 1) * (m - j + 1);
  }
  cout << ans << '\n';
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
