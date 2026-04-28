#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int board[MAX][MAX];
bool vis[MAX][MAX];

void solve() {
  int n, m, r, c, dir;
  cin >> n >> m >> r >> c >> dir;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  vis[r][c] = true;
  while (1) {
    bool found = false;
    for (int i = 0; i < 4; i++) {
      dir = (dir + 3) % 4;
      int nr = r + dx[dir], nc = c + dy[dir];

      if (vis[nr][nc] || board[nr][nc]) continue;

      found = true;
      r = nr, c = nc;
      vis[r][c] = true;
      break;
    }

    if (!found) {
      int nr = r - dx[dir], nc = c - dy[dir];
      if (board[nr][nc]) break;
      r = nr, c = nc;
    }

  }

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ans += vis[i][j];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
