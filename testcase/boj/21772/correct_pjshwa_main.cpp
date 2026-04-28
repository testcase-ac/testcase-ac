#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];
int vis[MAX][MAX];
int r, c, t;
int ans, cur;

void dfs(int i, int j, int ct) {
  if (t == ct) {
    ans = max(ans, cur);
    return;
  }

  if (i > 0 && board[i - 1][j] != '#') {
    if (board[i - 1][j] == 'S' && !vis[i - 1][j]) cur++;
    vis[i - 1][j]++;
    dfs(i - 1, j, ct + 1);
    vis[i - 1][j]--;
    if (board[i - 1][j] == 'S' && !vis[i - 1][j]) cur--;
  }
  if (j > 0 && board[i][j - 1] != '#') {
    if (board[i][j - 1] == 'S' && !vis[i][j - 1]) cur++;
    vis[i][j - 1]++;
    dfs(i, j - 1, ct + 1);
    vis[i][j - 1]--;
    if (board[i][j - 1] == 'S' && !vis[i][j - 1]) cur--;
  }
  if (i < r - 1 && board[i + 1][j] != '#') {
    if (board[i + 1][j] == 'S' && !vis[i + 1][j]) cur++;
    vis[i + 1][j]++;
    dfs(i + 1, j, ct + 1);
    vis[i + 1][j]--;
    if (board[i + 1][j] == 'S' && !vis[i + 1][j]) cur--;
  }
  if (j < c - 1 && board[i][j + 1] != '#') {
    if (board[i][j + 1] == 'S' && !vis[i][j + 1]) cur++;
    vis[i][j + 1]++;
    dfs(i, j + 1, ct + 1);
    vis[i][j + 1]--;
    if (board[i][j + 1] == 'S' && !vis[i][j + 1]) cur--;
  }
}

void solve() {
  cin >> r >> c >> t;
  for (int i = 0; i < r; i++) cin >> board[i];

  int si, sj;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    if (board[i][j] == 'G') si = i, sj = j;
  }
  dfs(si, sj, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
