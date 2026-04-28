#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000;
ll dp[MAXN + 1][MAXN + 1];

void solve() {
  int N, K, x; cin >> N >> K; ll ans = 0;
  for (int i = 1; i <= N; ++i) {
    cin >> x;
    for (int j = 0; j < i; ++j) {
      int k = max(0, i - K);
      dp[i][j] = max(dp[i][j], dp[j][k] + x);
      ans = max(ans, dp[i][j]);
    }
    for (int j = 1; j <= N; ++j) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
