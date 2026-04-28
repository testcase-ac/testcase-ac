#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXK = 100, MAXS = 5050, INF = 0x3f3f3f3f;
int dp[MAXK + 1][MAXS], A[MAXK], B[MAXK];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];
  for (int i = 0; i <= K; ++i) fill(dp[i], dp[i] + MAXS, -INF);
  dp[0][1] = 0;

  for (int k = 1; k <= K; ++k) for (int s = 1; s <= MAXS; ++s) {
    dp[k][s] = max(dp[k][s], dp[k - 1][s] + s);

    for (int i = 0; i < N; ++i) {
      if (B[i] <= s && dp[k - 1][s - B[i]] >= A[i]) {
        dp[k][s] = max(dp[k][s], dp[k - 1][s - B[i]] - A[i]);
      }
    }
  }

  int ans = 0;
  for (int s = 1; s <= MAXS; ++s) ans = max(ans, dp[K][s]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
