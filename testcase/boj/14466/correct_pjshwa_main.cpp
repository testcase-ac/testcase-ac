#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
bool board[MAX + 1][MAX + 1], vis[MAX + 1][MAX + 1];
bool wall[MAX + 1][MAX + 1][4];
int n;

int dfs(int i, int j) {
  vis[i][j] = true;
  int ans = board[i][j];

  if (i > 1 && !vis[i - 1][j] && !wall[i][j][0]) ans += dfs(i - 1, j);
  if (j < n && !vis[i][j + 1] && !wall[i][j][1]) ans += dfs(i, j + 1);
  if (i < n && !vis[i + 1][j] && !wall[i][j][2]) ans += dfs(i + 1, j);
  if (j > 1 && !vis[i][j - 1] && !wall[i][j][3]) ans += dfs(i, j - 1);

  return ans;
}

int main() {
  fast_io();

  int k, r;
  cin >> n >> k >> r;
  while (r--) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    if (r1 == r2) {
      if (c1 > c2) swap(c1, c2);
      wall[r1][c1][1] = true;
      wall[r1][c2][3] = true;
    }
    else {
      if (r1 > r2) swap(r1, r2);
      wall[r1][c1][2] = true;
      wall[r2][c1][0] = true;
    }
  }

  int ans = k * k;

  while (k--) {
    int r1, c1;
    cin >> r1 >> c1;
    board[r1][c1] = true;
  }

  int cur;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    if (!vis[i][j]) cur = dfs(i, j), ans -= cur * cur;
  }
  cout << ans / 2 << '\n';
}
