#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int board[MAX][MAX], vis[MAX][MAX];

void solve() {
  int n, m, T;
  cin >> n >> m >> T;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  queue<tii> q;
  q.push({0, 0, 0});
  vis[0][0] = 1;

  int res = -1;
  while (!q.empty()) {
    auto [x, y, c] = q.front();
    q.pop();

    if (x == n - 1 && y == m - 1) {
      if (res == -1) res = c;
      else res = min(res, c);
    }

    if (board[x][y] == 2) {
      int d = abs(n - 1 - x) + abs(m - 1 - y);
      if (res == -1) res = c + d;
      else res = min(res, c + d);
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      if (vis[nx][ny]) continue;
      if (board[nx][ny] == 1) continue;

      vis[nx][ny] = 1;
      q.push({nx, ny, c + 1});
    }
  }

  if (res == -1 || res > T) cout << "Fail\n";
  else cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
