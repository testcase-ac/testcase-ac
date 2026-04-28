#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MOD = 1e9 + 7;
ll dp[2][MAXN + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, K, x, cnt = 0; cin >> N >> K;
  for (int i = 0; i < N; ++i) {
    cin >> x; cnt += x;
  }

  memset(dp, 0, sizeof(dp));
  dp[0][cnt] = 1;

  for (int i = 1; i <= K; ++i) {
    int t = i & 1;
    memset(dp[t], 0, sizeof(dp[t]));

    for (int j = 0; j <= N; ++j) {
      if (j > 0) {
        ll val = dp[1 - t][j - 1] * (N - j + 1) % MOD;
        dp[t][j] = (dp[t][j] + val) % MOD;
      }
      if (j < N) {
        ll val = dp[1 - t][j + 1] * (j + 1) % MOD;
        dp[t][j] = (dp[t][j] + val) % MOD;
      }
    }
  }

  cout << dp[K & 1][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
