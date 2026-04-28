#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int board[300][300];
ll dp[300][300];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) cin >> board[i][j];
  }

  dp[0][0] = board[0][0];
  for (int i = 1; i < n; i++) dp[i][0] = dp[i - 1][0] + board[i][0];
  for (int i = 1; i < m; i++) dp[0][i] = dp[0][i - 1] + board[0][i];

  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + board[i][j];
    }
  }

  cout << dp[n - 1][m - 1] << '\n';
}
