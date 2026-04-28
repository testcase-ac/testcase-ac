#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int INF = 1e9;
int dp[501][501];
int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  for (int i = 1; i <= n; i++) dp[i][1] = i;
  for (int i = 1; i <= n; i++) {
    for (int j = 2; j <= k; j++) {
      dp[i][j] = INF;
      for (int s = 1; s <= i; s++) dp[i][j] = min(dp[i][j], max(dp[s - 1][j - 1], dp[i - s][j]) + 1);
    }
  }

  cout << dp[n][k] << '\n';
}
