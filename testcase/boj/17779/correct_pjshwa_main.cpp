#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int board[MAX + 1][MAX + 1], vis[MAX + 1][MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> board[i][j];

  int ans = 1e9;
  for (int x = 1; x <= n; x++) for (int y = 1; y <= n; y++) {
    for (int d1 = 1; d1 <= n; d1++) for (int d2 = 1; d2 <= n; d2++) {
      if (x + d1 + d2 > n || y - d1 < 1 || y + d2 > n) continue;

      memset(vis, 0, sizeof(vis));
      for (int i = 0; i <= d1; i++) vis[x + i][y - i] = 5;
      for (int i = 0; i <= d2; i++) vis[x + i][y + i] = 5;
      for (int i = 0; i <= d2; i++) vis[x + d1 + i][y - d1 + i] = 5;
      for (int i = 0; i <= d1; i++) vis[x + d2 + i][y + d2 - i] = 5;

      for (int i = 0; i < d1; i++) {
        int j = 1;
        while (1) {
          if (vis[x + i + j][y - i] == 5) break;
          else vis[x + i + j][y - i] = 5, j++;
        }
      }
      for (int i = 1; i < d2; i++) {
        int j = 1;
        while (1) {
          if (vis[x + i + j][y + i] == 5) break;
          else vis[x + i + j][y + i] = 5, j++;
        }
      }

      int v[5] = {0};
      for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        if (vis[i][j] == 5) v[4] += board[i][j];
        else if (i < x + d1 && j <= y) v[0] += board[i][j];
        else if (i <= x + d2 && j > y) v[1] += board[i][j];
        else if (i >= x + d1 && j < y - d1 + d2) v[2] += board[i][j];
        else if (i > x + d2 && j >= y - d1 + d2) v[3] += board[i][j];
      }

      ans = min(
        ans,
        *max_element(v, v + 5) - *min_element(v, v + 5)
      );
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
