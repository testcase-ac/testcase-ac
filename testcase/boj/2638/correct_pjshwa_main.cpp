#include <bits/stdc++.h>
using namespace std;

const int MAX = 105;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int board[MAX][MAX];
int n, m;
bool mark[MAX][MAX];

void dfs(int i, int j) {
  mark[i][j] = true;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m || mark[nx][ny] || board[nx][ny] == 1) continue;
    dfs(nx, ny);
  }
}

int erase() {
  int erased = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] != 1) continue;

    int marked = 0;
    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (mark[nx][ny]) marked++;
    }
    if (marked >= 2) erased++, board[i][j] = 0;
  }
  return erased;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  int t = 0;
  while (1) {
    memset(mark, false, sizeof(mark));
    dfs(0, 0);
    if (!erase()) break;
    t++;
  }

  cout << t << '\n';
}
