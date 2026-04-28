#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXM = 50;
char board[2][MAXM + 1];
int dp[MAXM][2][2];

void solve() {
  int M; cin >> M;
  cin >> board[0] >> board[1];

  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < M; ++i) {
    for (int pr0 = 0; pr0 < 2; ++pr0) for (int pr1 = 0; pr1 < 2; ++pr1) 
    for (int r0 = 0; r0 < 2; ++r0) for (int r1 = 0; r1 < 2; ++r1) {
      if (i > 0) {
        if (pr0 == 1 && r1 == 1) continue;
        if (pr1 == 1 && r0 == 1) continue;
        if (pr0 == 1 && pr1 == 1) continue;
        if (dp[i - 1][pr0][pr1] == -1) continue;
      }
      if (r0 == 0 && board[0][i] == '#') continue;
      if (r1 == 0 && board[1][i] == '#') continue;
      if (r0 == 1 && r1 == 1) continue;

      int add = 0;
      if (r0 == 1 && board[0][i] == '.') ++add;
      if (r1 == 1 && board[1][i] == '.') ++add;

      if (i > 0) dp[i][r0][r1] = max(dp[i][r0][r1], dp[i - 1][pr0][pr1] + add);
      else dp[i][r0][r1] = add;
    }
  }

  int ans = -1;
  for (int r0 = 0; r0 < 2; ++r0) for (int r1 = 0; r1 < 2; ++r1) {
    ans = max(ans, dp[M - 1][r0][r1]);
  }
  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
