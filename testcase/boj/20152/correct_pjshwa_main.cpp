#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

long long dp[31][31];
int main() {
  fast_io();

  int h, n;
  cin >> h >> n;
  int diff = abs(h - n);

  for (int i = 0; i <= diff; i++) dp[0][i] = 1;
  for (int i = 1; i <= diff; i++) {
    for (int j = i; j <= diff; j++) dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
  }

  cout << dp[diff][diff] << '\n';
}
