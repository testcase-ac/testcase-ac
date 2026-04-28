#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, INF = 0x3f3f3f3f;

// i-th index, cooltime j
int dp[MAX + 1][4];

void solve() {
  int N; cin >> N;

  fill(dp[0], dp[0] + 4, -INF); dp[0][0] = 0;
  for (int i = 1; i <= N; ++i) {
    fill(dp[i], dp[i] + 4, -INF);

    int x; cin >> x;
    dp[i][0] = max(dp[i][0], dp[i - 1][0] + x);
    dp[i][0] = max(dp[i][0], dp[i - 1][1] + x);
    dp[i][1] = max(dp[i][1], dp[i - 1][2] + 2 * x);
    dp[i][2] = max(dp[i][2], dp[i - 1][3] + 2 * x);
    dp[i][3] = max(dp[i][3], dp[i - 1][0] + 2 * x);
    dp[i][3] = max(dp[i][3], dp[i - 1][1] + 2 * x);
  }

  int ans = -INF;
  for (int j = 0; j < 4; ++j) ans = max(ans, dp[N][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
