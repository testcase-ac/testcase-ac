#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

char board[51][51];
int n, m;

int vis[50][50];
const pii dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool dfs(int x, int y, int px, int py) {
  int dx, dy, nx, ny;
  vis[x][y] = -1;

  bool res = false;
  for (int i = 0; i < 4; i++) {
    tie(dx, dy) = dirs[i];
    nx = x + dx;
    ny = y + dy;
    if (nx > n - 1 || nx < 0 || ny > m - 1 || ny < 0) continue;
    if (nx == px && ny == py) continue;
    if (board[x][y] != board[nx][ny]) continue;

    if (vis[nx][ny] == -1) return true;
    else if (vis[nx][ny] == 0) res |= dfs(nx, ny, x, y);
  }

  vis[x][y] = 1;
  return res;
}

int main() {
  fast_io();

  bool has_cycle = false;

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j]) {
        has_cycle |= dfs(i, j, -1, -1);
        if (has_cycle) break;
      }
    }
    if (has_cycle) break;
  }

  cout << (has_cycle ? "Yes" : "No") << '\n';
}
