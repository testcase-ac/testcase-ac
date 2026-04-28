#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
double a[MAX + 1];

void solve() {
  int n, k; cin >> n >> k;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  sort(a + 1, a + n + 1, greater<double>());

  vector<vector<double>> dp(n + 1, vector<double>(2 * n + 1, 0.0));
  dp[0][n] = 1; double ans = 0;

  for (int i = 1; i <= n; ++i) {
    for (int l = 0; l <= 2 * n; ++l) {
      if (l > 0) dp[i][l] += dp[i - 1][l - 1] * a[i];
      if (l < 2 * n) dp[i][l] += dp[i - 1][l + 1] * (1 - a[i]);
    }

    double cur = 0;
    for (int l = k + n; l <= 2 * n; ++l) cur += dp[i][l];
    ans = max(ans, cur);
  }
  cout << fixed << setprecision(9) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
