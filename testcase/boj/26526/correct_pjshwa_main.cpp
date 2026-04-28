#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000, MOD = 1e9 + 7;
int dp[MAXN + 1][MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;

  dp[1][1] = 1;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
    if (i != N && i == j) continue;

    for (int pi = max(1, i - K); pi < i; ++pi) {
      dp[i][j] = (dp[i][j] + dp[pi][j]) % MOD;
    }
    for (int pj = max(1, j - K); pj < j; ++pj) {
      dp[i][j] = (dp[i][j] + dp[i][pj]) % MOD;
    }

    cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << '\n';
  }

  cout << dp[N][N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
