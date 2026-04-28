#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4, MAXK = 500;
ll A[MAXN + MAXK + 1], dp[MAXK + 1][MAXN + MAXK + 1];

void solve() {
  int N, K, W; cin >> N >> K >> W;

  for (int i = 1; i <= N; ++i) cin >> A[i], A[i] += A[i - 1];
  for (int i = N + 1; i <= N + W; ++i) A[i] = A[N];
  N += W;

  for (int i = 0; i <= K; ++i) fill(dp[i], dp[i] + N + 1, 0);

  ll ans = 0;
  for (int k = 1; k <= K; ++k) {
    for (int i = 1; i <= N; ++i) {
      int p = max(0, i - W);
      dp[k][i] = max(dp[k][i - 1], dp[k - 1][p] + A[i] - A[p]);

      for (int j = 1; j <= W; ++j) {
        int r = p - j;
        if (k < 2 || r < 0) break;
        dp[k][i] = max(dp[k][i], dp[k - 2][r] + A[i] - A[r]);
      }

      ans = max(ans, dp[k][i]);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
