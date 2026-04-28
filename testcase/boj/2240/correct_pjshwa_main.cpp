#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN + 1], dp[MAXN + 1][2][31];

void solve() {
  int N, W; cin >> N >> W;
  for (int i = 1; i <= N; ++i) cin >> A[i], --A[i];

  memset(dp, -1, sizeof dp); dp[0][0][0] = 0;
  for (int i = 1; i <= N; ++i) {
    for (int w = 0; w <= W; ++w) {
      if (dp[i - 1][0][w] != -1) dp[i][0][w] = dp[i - 1][0][w] + (A[i] == 0);
      if (dp[i - 1][1][w] != -1) dp[i][1][w] = dp[i - 1][1][w] + (A[i] == 1);
    }
    for (int w = 0; w < W; ++w) {
      if (dp[i - 1][1][w] != -1) {
        dp[i][0][w + 1] = max(dp[i][0][w + 1], dp[i - 1][1][w] + (A[i] == 0));
      }
      if (dp[i - 1][0][w] != -1) {
        dp[i][1][w + 1] = max(dp[i][1][w + 1], dp[i - 1][0][w] + (A[i] == 1));
      }
    }
  }

  int ans = 0;
  for (int w = 0; w <= W; ++w) ans = max({ans, dp[N][0][w], dp[N][1][w]});
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
