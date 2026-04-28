#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2e5, MAXK = 40, LIM = 1e11;
ll dp[MAXN + 1][MAXK + 1];

void solve() {
  int N, K, s; cin >> N >> K >> s;
  if (K >= MAXK) return cout << "MEGA\n", void();

  memset(dp, -1, sizeof dp);
  dp[0][0] = s;

  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    for (int k = 0; k <= K; ++k) {
      if (dp[i - 1][k] <= 0) continue;
      dp[i][k] = dp[i - 1][k] + x;
    }
    for (int k = 0; k < K; ++k) {
      if (dp[i - 1][k] <= 0) continue;
      dp[i][k + 1] = max(dp[i][k + 1], dp[i - 1][k] * 2);
    }
    for (int k = 0; k <= K; ++k) {
      if (dp[i][k] > 1e12) return cout << "MEGA\n", void();
    }
  }

  ll ans = 0;
  for (int k = 0; k <= K; ++k) ans = max(ans, dp[N][k]);
  if (ans > LIM) cout << "MEGA\n";
  else if (ans == 0) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
