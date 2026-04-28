#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MOD = 1e9 + 7;
int dp[MAXN + 5][MAXN + 5][2];

void solve() {
  int N; string S; cin >> N >> S;
  S = ' ' + S;

  if (N % 3) return cout << "0\n", void();
  int Yc = N / 3;

  // (index, y count, y appeared last)
  for (int i = 0; i <= N; ++i) for (int j = 0; j <= Yc; ++j) {
    dp[i][j][0] = dp[i][j][1] = 0;
  }
  dp[0][0][0] = 1;

  for (int i = 1; i <= N; ++i) for (int y = 0; y <= Yc; ++y) {
    // Write H
    if (S[i] != 'Y') {
      dp[i][y][0] = (dp[i][y][0] + dp[i - 1][y][1]) % MOD;
      dp[i][y][0] = (dp[i][y][0] + dp[i - 1][y][0]) % MOD;
    }

    // Write Y
    if (i > 1 && i < N && y > 0 && S[i] != 'H') {
      dp[i][y][1] = (dp[i][y][1] + dp[i - 1][y - 1][0]) % MOD;
    }
  }

  cout << dp[N][Yc][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
