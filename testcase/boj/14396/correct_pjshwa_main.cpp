#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000, MOD = 1e9 + 9;
int d[2][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;

  d[0][0] = 1;
  for (int i = 1; i < n; i++) {
    int x = i & 1;
    for (int t = m; t >= 0; t--) d[x][t] = 0;
    for (int t = m; t >= 0; t--) {
      int w = t > i ? d[1 - x][t - i - 1] : 0;
      d[x][t] = (d[x][t] + (d[1 - x][t] + MOD - w) % MOD) % MOD;
    }
    for (int t = 1; t <= m; t++) d[x][t] = (d[x][t] + d[x][t - 1]) % MOD;
  }

  int ans = 0;
  for (int t = m; t >= 0; t -= 2) ans = (ans + d[(n - 1) & 1][t]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
