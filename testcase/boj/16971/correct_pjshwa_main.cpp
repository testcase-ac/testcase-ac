#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];

  ll ans = 0;
  for (int i = 0; i < n - 1; i++) for (int j = 0; j < m - 1; j++) {
    ans += a[i][j] + a[i][j + 1] + a[i + 1][j] + a[i + 1][j + 1];
  }

  ll sum0, sum1, osum = ans;

  sum0 = sum1 = 0;
  for (int j = 0; j < m; j++) sum0 += a[0][j] * ((j == 0 || j == m - 1) ? 1 : 2);
  for (int j = 0; j < m; j++) sum1 += a[n - 1][j] * ((j == 0 || j == m - 1) ? 1 : 2);
  for (int i = 1; i < n - 1; i++) {
    ll sumc = 0;
    for (int j = 0; j < m; j++) sumc += a[i][j] * ((j == 0 || j == m - 1) ? 1 : 2);
    ans = max(ans, osum - sumc + sum0);
    ans = max(ans, osum - sumc + sum1);
  }

  sum0 = sum1 = 0;
  for (int i = 0; i < n; i++) sum0 += a[i][0] * ((i == 0 || i == n - 1) ? 1 : 2);
  for (int i = 0; i < n; i++) sum1 += a[i][m - 1] * ((i == 0 || i == n - 1) ? 1 : 2);
  for (int j = 1; j < m - 1; j++) {
    ll sumc = 0;
    for (int i = 0; i < n; i++) sumc += a[i][j] * ((i == 0 || i == n - 1) ? 1 : 2);
    ans = max(ans, osum - sumc + sum0);
    ans = max(ans, osum - sumc + sum1);
  }

  cout << ans << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
