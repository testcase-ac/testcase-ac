#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXK = 4, INF = 0x3f3f3f3f;
int A[MAXN + 1], B[MAXN + 1], dp[MAXN + 1][MAXK + 1][2];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 1; i <= N; ++i) cin >> B[i];

  for (int i = 0; i <= N; ++i) {
    for (int k = 0; k <= K; ++k) dp[i][k][0] = dp[i][k][1] = -INF;
  }
  dp[0][0][0] = 0;

  for (int i = 1; i <= N; ++i) for (int k = 0; k <= K; ++k) {
    dp[i][k][0] = dp[i - 1][k][0] + A[i];
    if (k > 0) dp[i][k][0] = max(dp[i][k][0], dp[i - 1][k - 1][1] + A[i]);

    dp[i][k][1] = dp[i - 1][k][1] + B[i];
    if (k > 0) dp[i][k][1] = max(dp[i][k][1], dp[i - 1][k - 1][0] + B[i]);
  }

  int ans = -INF;
  for (int k = 0; k <= K; ++k) {
    ans = max({ans, dp[N][k][0], dp[N][k][1]});
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
