#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, board[10][10];
bool l[10], r[10];
int ans[2], ccol;

void dfs(int row, int col, int v) {
  ans[ccol] = max(ans[ccol], v);
  if (col >= n) {
    row++;
    if (row == n) return;
    col = ccol ^ (row & 1);
  }

  if (board[row][col] && !l[col - row + n - 1] && !r[row + col]) {
    l[col - row + n - 1] = r[row + col] = true;
    dfs(row, col + 2, v + 1);
    l[col - row + n - 1] = r[row + col] = false;
  }
  dfs(row, col + 2, v);
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];
  dfs(0, 0, 0);
  ccol++;
  dfs(0, 1, 0);
  cout << ans[0] + ans[1];
}
