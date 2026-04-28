#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool vis[500][500];
int board[500][500];
int n, m;
int dfs(int i, int j) {
  vis[i][j] = 1;
  int cc = 1;

  if (i > 0 && !vis[i - 1][j] && board[i - 1][j] == 1) cc += dfs(i - 1, j);
  if (i < n - 1 && !vis[i + 1][j] && board[i + 1][j] == 1) cc += dfs(i + 1, j);
  if (j > 0 && !vis[i][j - 1] && board[i][j - 1] == 1) cc += dfs(i, j - 1);
  if (j < m - 1 && !vis[i][j + 1] && board[i][j + 1] == 1) cc += dfs(i, j + 1);
  return cc;
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) cin >> board[i][j];
  }

  int c = 0, a = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j] && board[i][j] == 1) {
        c++;
        a = max(a, dfs(i, j));
      }
    }
  }

  cout << c << '\n' << a << '\n';
}
