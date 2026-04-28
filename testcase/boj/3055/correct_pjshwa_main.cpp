#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int r, c, fl[51][51];
bool vis[51][51];
char board[51][51];

void flood_bfs(int si, int sj) {
  queue<pair<pair<int, int>, int>> q;
  q.push({{si, sj}, 0});

  while (!q.empty()) {
    auto[ni, nj] = q.front().first;
    int nd = q.front().second;
    q.pop();

    if (vis[ni][nj]) continue;
    vis[ni][nj] = true;
    fl[ni][nj] = nd;

    if (ni > 0 && !vis[ni - 1][nj] && board[ni - 1][nj] == '.') q.push({{ni - 1, nj}, nd + 1});
    if (ni < r - 1 && !vis[ni + 1][nj] && board[ni + 1][nj] == '.') q.push({{ni + 1, nj}, nd + 1});
    if (nj > 0 && !vis[ni][nj - 1] && board[ni][nj - 1] == '.') q.push({{ni, nj - 1}, nd + 1});
    if (nj < c - 1 && !vis[ni][nj + 1] && board[ni][nj + 1] == '.') q.push({{ni, nj + 1}, nd + 1}); 
  }
}

int move_bfs(int si, int sj) {
  queue<pair<pair<int, int>, int>> q;
  q.push({{si, sj}, 0});

  while (!q.empty()) {
    auto[ni, nj] = q.front().first;
    int nd = q.front().second;
    q.pop();

    if (board[ni][nj] == 'D') return nd;

    if (vis[ni][nj]) continue;
    vis[ni][nj] = true;

    if (ni > 0 && !vis[ni - 1][nj] && fl[ni - 1][nj] > nd + 1) q.push({{ni - 1, nj}, nd + 1});
    if (ni < r - 1 && !vis[ni + 1][nj] && fl[ni + 1][nj] > nd + 1) q.push({{ni + 1, nj}, nd + 1});
    if (nj > 0 && !vis[ni][nj - 1] && fl[ni][nj - 1] > nd + 1) q.push({{ni, nj - 1}, nd + 1});
    if (nj < c - 1 && !vis[ni][nj + 1] && fl[ni][nj + 1] > nd + 1) q.push({{ni, nj + 1}, nd + 1});
  }

  return -1;
}

int main() {
  fast_io();

  cin >> r >> c;
  for (int i = 0; i < r; i++) cin >> board[i];

  // Initialize map
  int si, sj;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    if (board[i][j] == 'S') si = i, sj = j, board[i][j] = '.';
    if (board[i][j] != 'X') fl[i][j] = 9999;
  }

  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    if (board[i][j] == '*') flood_bfs(i, j);
  }

  memset(vis, 0, sizeof(vis));
  int ans = move_bfs(si, sj);
  if (ans == -1) cout << "KAKTUS";
  else cout << ans;
}
