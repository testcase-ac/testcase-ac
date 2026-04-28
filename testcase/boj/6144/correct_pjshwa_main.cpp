#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXM = 12880, INF = 0x3f3f3f3f;
int dp[2][MAXM + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int j = 0; j <= M; ++j) dp[0][j] = dp[1][j] = -INF;
  dp[0][0] = 0;

  for (int i = 1; i <= N; ++i) {
    int x = (i & 1);
    for (int j = 0; j <= M; ++j) dp[x][j] = dp[1 - x][j];

    int w, d; cin >> w >> d;
    for (int j = w; j <= M; ++j) {
      dp[x][j] = max(dp[x][j], dp[1 - x][j - w] + d);
    }
  }

  int ans = 0;
  for (int j = 0; j <= M; ++j) ans = max(ans, dp[N & 1][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
