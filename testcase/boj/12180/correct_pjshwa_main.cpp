#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 25;
ll dp[MAXN + 1][MAXN + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int R, C; cin >> R >> C;
  cout << dp[R][C] << '\n';
}

int main() {
  fast_io();

  for (int i = 1; i <= MAXN; ++i) dp[i][1] = dp[1][i] = 1;
  for (int i = 2; i <= MAXN; ++i) for (int j = 2; j <= MAXN; ++j) {
    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
