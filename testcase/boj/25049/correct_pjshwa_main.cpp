#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
ll a[MAX + 1], d[MAX + 1][5];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int j = 0; j < 5; j++) d[0][j] = 0;
  for (int i = 1; i <= n; i++) {
    d[i][0] = d[i - 1][0] + a[i];
    d[i][1] = max(d[i - 1][1], d[i - 1][0]) + 2 * a[i];
    d[i][2] = max(d[i - 1][2], d[i - 1][1]) + a[i];
    d[i][3] = max(d[i - 1][3], d[i - 1][2]) + 2 * a[i];
    d[i][4] = max(d[i - 1][4], d[i - 1][3]) + a[i];
  }

  ll ans = -1e18;
  for (int j = 0; j < 5; j++) ans = max(ans, d[n][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
