#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int dp[2][62501];
int main() {
  fast_io();

  int n, k, s;
  cin >> n >> k;
  if (k > n * (n - 1) / 4) k = n * (n - 1) / 2 - k;

  dp[1][0] = 1;
  for (int i = 2; i <= n; i++) {
    s = 0;
    for (int j = 0; j <= k; j++) {
      s += dp[(i + 1) % 2][j];
      if (j >= i) s -= dp[(i + 1) % 2][j - i];
      s = (s + 30011) % 30011;
      dp[i % 2][j] = s;
    }
  }

  cout << dp[n % 2][k] << '\n';
}
