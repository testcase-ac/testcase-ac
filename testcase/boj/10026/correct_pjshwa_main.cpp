#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n;
bool visited[100][100];
char board[101][100];

void dfs(int r, int c) {
  char cur = board[r][c];
  visited[r][c] = true;
  if (r > 0 && board[r - 1][c] == cur && !visited[r - 1][c]) dfs(r - 1, c);
  if (r < n - 1 && board[r + 1][c] == cur && !visited[r + 1][c]) dfs(r + 1, c);
  if (c > 0 && board[r][c - 1] == cur && !visited[r][c - 1]) dfs(r, c - 1);
  if (c < n - 1 && board[r][c + 1] == cur && !visited[r][c + 1]) dfs(r, c + 1);
}

void dfs2(int r, int c) {
  char cur = board[r][c];
  visited[r][c] = true;

  if (cur == 'B') {
    if (r > 0 && board[r - 1][c] == cur && !visited[r - 1][c]) dfs2(r - 1, c);
    if (r < n - 1 && board[r + 1][c] == cur && !visited[r + 1][c]) dfs2(r + 1, c);
    if (c > 0 && board[r][c - 1] == cur && !visited[r][c - 1]) dfs2(r, c - 1);
    if (c < n - 1 && board[r][c + 1] == cur && !visited[r][c + 1]) dfs2(r, c + 1);
  }
  else {
    if (r > 0 && (board[r - 1][c] == 'R' || board[r - 1][c] == 'G') && !visited[r - 1][c]) dfs2(r - 1, c);
    if (r < n - 1 && (board[r + 1][c] == 'R' || board[r + 1][c] == 'G') && !visited[r + 1][c]) dfs2(r + 1, c);
    if (c > 0 && (board[r][c - 1] == 'R' || board[r][c - 1] == 'G') && !visited[r][c - 1]) dfs2(r, c - 1);
    if (c < n - 1 && (board[r][c + 1] == 'R' || board[r][c + 1] == 'G') && !visited[r][c + 1]) dfs2(r, c + 1);
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];

  int cnt = 0, cnt2 = 0;

  memset(visited, false, sizeof(visited));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!visited[i][j]) {
        cnt++;
        dfs(i, j);
      }
    }
  }

  memset(visited, false, sizeof(visited));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!visited[i][j]) {
        cnt2++;
        dfs2(i, j);
      }
    }
  }

  cout << cnt << ' ' << cnt2 << '\n';
}
