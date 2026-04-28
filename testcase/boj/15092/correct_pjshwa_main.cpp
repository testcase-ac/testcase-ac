#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];
int n, m;

void dfs(int i, int j) {
  vis[i][j] = true;

  if (i > 0 && !vis[i - 1][j] && board[i - 1][j] == '#') dfs(i - 1, j);
  if (j > 0 && !vis[i][j - 1] && board[i][j - 1] == '#') dfs(i, j - 1);
  if (i < n - 1 && !vis[i + 1][j] && board[i + 1][j] == '#') dfs(i + 1, j);
  if (j < m - 1 && !vis[i][j + 1] && board[i][j + 1] == '#') dfs(i, j + 1);

  if (i > 0 && j > 0 && !vis[i - 1][j - 1] && board[i - 1][j - 1] == '#') dfs(i - 1, j - 1);
  if (i < n - 1 && j < m - 1 && !vis[i + 1][j + 1] && board[i + 1][j + 1] == '#') dfs(i + 1, j + 1);
  if (i > 0 && j < m - 1 && !vis[i - 1][j + 1] && board[i - 1][j + 1] == '#') dfs(i - 1, j + 1);
  if (i < n - 1 && j > 0 && !vis[i + 1][j - 1] && board[i + 1][j - 1] == '#') dfs(i + 1, j - 1);
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  int cc = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (!vis[i][j] && board[i][j] == '#') cc++, dfs(i, j);
  }
  cout << cc << '\n';
}
