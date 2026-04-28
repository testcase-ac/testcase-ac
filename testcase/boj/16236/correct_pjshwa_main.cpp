#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, t;
int ssz = 2, rem = 2;
int board[20][20];
bool vis[20][20];
pii pos;

bool bfs() {
  memset(vis, 0, sizeof(vis));

  queue<pair<pii, int>> q;
  q.push({pos, 0});

  pii npos;
  int nx, ny, nd;
  int dx = -1, dy = -1, dd = 1e9;

  while (!q.empty()) {
    tie(npos, nd) = q.front();
    tie(nx, ny) = npos;
    q.pop();

    if (vis[nx][ny]) continue;
    vis[nx][ny] = true;

    if (board[nx][ny] >= 1 && board[nx][ny] < ssz) {
      if (
        nd < dd ||
        nd == dd && nx < dx ||
        nd == dd && nx == dx && ny < dy
      ) tie(dx, dy, dd) = {nx, ny, nd};
    }

    if (nx > 0 && !vis[nx - 1][ny] && board[nx - 1][ny] <= ssz) q.push({{nx - 1, ny}, nd + 1});
    if (ny > 0 && !vis[nx][ny - 1] && board[nx][ny - 1] <= ssz) q.push({{nx, ny - 1}, nd + 1});
    if (nx < n - 1 && !vis[nx + 1][ny] && board[nx + 1][ny] <= ssz) q.push({{nx + 1, ny}, nd + 1});
    if (ny < n - 1 && !vis[nx][ny + 1] && board[nx][ny + 1] <= ssz) q.push({{nx, ny + 1}, nd + 1});
  }

  if (dx == -1) return false;
  else {
    if (!--rem) {
      ssz++;
      rem = ssz;
    }
    board[dx][dy] = 0;
    t += dd;
    pos = {dx, dy};
    return true;
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
      if (board[i][j] == 9) {
        pos = {i, j};
        board[i][j] = 0;
      }
    }
  }

  while (bfs()) {}
  cout << t;
}
