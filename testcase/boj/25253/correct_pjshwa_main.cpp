#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200, MAXM = 10;
int f[MAXM + 1][MAXM + 1][MAXM + 1], s[MAXN + 1];

// (index, state_1, state_2)
bool dp[MAXN + 1][MAXM + 1][MAXM + 1];

void solve() {
  int n, m; cin >> n >> m;
  for (int x = 1; x <= m; ++x) for (int y = 1; y <= m; ++y) for (int z = 1; z <= m; ++z) {
    cin >> f[x][y][z];
  }
  for (int i = 1; i <= n; ++i) cin >> s[i];

  for (int state_n = 1; state_n <= m; ++state_n) for (int state_1 = 1; state_1 <= m; ++state_1) {

    memset(dp, false, sizeof(dp));
    for (int j = 1; j <= m; ++j) {
      if (f[state_n][state_1][j] == s[1]) dp[1][state_1][j] = true;
    }

    for (int i = 2; i <= n - 1; ++i) {
      for (int pre1 = 1; pre1 <= m; ++pre1)
      for (int pre2 = 1; pre2 <= m; ++pre2) {
        if (!dp[i - 1][pre1][pre2]) continue;
        for (int nxt = 1; nxt <= m; ++nxt) {
          if (f[pre1][pre2][nxt] == s[i]) {
            dp[i][pre2][nxt] = true;
          }
        }
      }
    }

    for (int pre1 = 1; pre1 <= m; ++pre1) {
      if (!dp[n - 1][pre1][state_n]) continue;
      if (f[pre1][state_n][state_1] == s[n]) {
        cout << "yes\n";
        return;
      }
    }
  }

  cout << "no\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
