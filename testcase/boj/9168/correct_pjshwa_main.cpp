#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};
string board[MAX + 1];
bool vis[MAX][MAX][4];
int ex, ey;

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin.ignore();
    getline(cin, board[i]);
  }
  memset(vis, 0, sizeof(vis));

  queue<tuple<int, int, int, int>> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'S') {
      for (int k = 0; k < 4; k++) {
        vis[i][j][k] = true;
        q.push({i, j, k, 0});
      }
    }
    if (board[i][j] == 'F') {
      ex = i, ey = j;
    }
  }

  while (!q.empty()) {
    auto [x, y, k, cnt] = q.front();
    q.pop();

    if (x == ex && y == ey) {
      cout << cnt << '\n';
      return;
    }

    for (int u = 0; u < 2; u++) {
      int i = (u + k) % 4;
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      if (vis[nx][ny][i] || board[nx][ny] == 'X') continue;
      vis[nx][ny][i] = true;
      q.push({nx, ny, i, cnt + 1});
    }

  }
}

int main() {
  fast_io();
 
  int t = 1;
  cin >> t;
  while (t--) solve();
}
