#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, INF = 1e9 + 7;
int board[MAX + 1][MAX + 1];

void solve() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> board[i][j];
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    board[i][j] = board[i][j] + board[i - 1][j] + board[i][j - 1] - board[i - 1][j - 1];
  }

  int ans = INF;
  for (int i = 0; i < (1 << (n - 1)); i++) {
    if (__builtin_popcount(i) != a) continue;

    for (int j = 0; j < (1 << (m - 1)); j++) {
      if (__builtin_popcount(j) != b) continue;

      int cur = 0, lastii = 0;
      for (int ii = 0; ii < n; ii++) {
        if (ii < n - 1 && !(i & (1 << ii))) continue;

        int lastjj = 0;
        for (int jj = 0; jj < m; jj++) {
          if (jj < m - 1 && !(j & (1 << jj))) continue;

          cur = max(cur, board[ii + 1][jj + 1] - board[lastii][jj + 1] - board[ii + 1][lastjj] + board[lastii][lastjj]);
          lastjj = jj + 1;
        }
        lastii = ii + 1;
      }
      ans = min(ans, cur);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
