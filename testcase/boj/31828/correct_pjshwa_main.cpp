#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MOD = 1e9 + 7;
ll dp[MAXN + 1][5];

void solve() {
  int N; cin >> N;

  dp[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < 5; ++j) dp[i][j] = dp[i - 1][j] * 25;
    dp[i][0] = (dp[i][0] + dp[i - 1][0]) % MOD;
    for (int j = 1; j < 5; ++j) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
  }
  cout << dp[N][4] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
