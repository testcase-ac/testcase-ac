#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3;
int du[MAX][MAX], dd[MAX][MAX], board[MAX][MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  du[n - 1][0] = board[n - 1][0];
  for (int i = n - 2; i >= 0; i--) du[i][0] = du[i + 1][0] + board[i][0];
  for (int j = 1; j < m; j++) du[n - 1][j] = board[n - 1][j] + du[n - 1][j - 1];
  for (int i = n - 2; i >= 0; i--) for (int j = 1; j < m; j++) {
    du[i][j] = board[i][j] + max(du[i][j - 1], du[i + 1][j]);
  }

  dd[n - 1][m - 1] = board[n - 1][m - 1];
  for (int i = n - 2; i >= 0; i--) dd[i][m - 1] = dd[i + 1][m - 1] + board[i][m - 1];
  for (int j = m - 2; j >= 0; j--) dd[n - 1][j] = board[n - 1][j] + dd[n - 1][j + 1];
  for (int i = n - 2; i >= 0; i--) for (int j = m - 2; j >= 0; j--) {
    dd[i][j] = board[i][j] + max(dd[i][j + 1], dd[i + 1][j]);
  }

  int ans = -1e9;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    ans = max(ans, du[i][j] + dd[i][j]);
  }

  cout << ans;
}
