#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, INF = 1e9 + 7;
bool board[MAX][MAX];

void solve() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < m; j++) board[i][j] = s[j] == '#';
  }

  bool target[MAX][MAX];
  int dx[7] = {0, 0, 0, 1, 2, 2, 2}, dy[7] = {0, 1, 2, 0, 0, 1, 2};
  int ans = INF;

  for (int d = 1; d <= 7; d++) {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
      if (i + 3 * d - 1 >= n || j + 3 * d - 1 >= m) continue;

      memset(target, 0, sizeof(target));
      for (int u = 0; u < 7; u++) for (int ii = 0; ii < d; ii++) for (int jj = 0; jj < d; jj++) {
        int x = i + dx[u] * d + ii, y = j + dy[u] * d + jj;
        target[x][y] = 1;
      }

      int cur = 0;
      for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (target[i][j] == 1 && board[i][j] == 0) cur += a;
        if (target[i][j] == 0 && board[i][j] == 1) cur += b;
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
