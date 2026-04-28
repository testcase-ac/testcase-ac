#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MOD = 1e9 + 9;
int dp[2][501 * 501];
int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;

  for(int i = 0; i <= n; i++) dp[1][i] = 1;
  for(int i = 2; i <= m; i++) {
    dp[i % 2][0] = 1;

    for (int j = 1; j <= n * i; j++) {
      dp[i % 2][j] = (dp[i % 2][j - 1] + dp[(i - 1) % 2][j]) % MOD;
      if (j - n - 1 >= 0)
        dp[i % 2][j] = (dp[i % 2][j] - dp[(i - 1) % 2][j - n - 1] + MOD) % MOD;
    }
  }

  cout << dp[m % 2][k] << '\n';
}
