#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;
int board[MAX + 10][MAX + 10], n, m;
int dw[MAX + 10][MAX + 10], dm[MAX + 10][MAX + 10];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> board[i][j];

  for (int i = 1; i <= n; i++) dw[i][1] = board[i][1];
  for (int j = 2; j <= m + 1; j++) for (int i = 1; i <= n; i++) {
    dw[i][j] = max({dw[i - 1][j - 1], dw[i + 1][j - 1], dw[i][j - 2] + board[i][j - 1]}) + board[i][j];
  }

  dm[0][1] = board[1][1];
  for (int i = 1; i <= n; i++) dm[i][1] = max(board[i][1], board[i + 1][1]);
  for (int j = 2; j <= m; j++) for (int i = 0; i <= n; i++) {
    dm[i][j] = dm[i + 1][j - 1] + board[i + 1][j];
    if (i > 0) dm[i][j] = max(dm[i][j], dm[i - 1][j - 1] + board[i][j]);
  }

  int mx = 0;
  for (int i = 1; i <= n; i++) mx = max({mx, dw[i][m], dw[i][m + 1]});
  for (int i = 0; i <= n; i++) mx = max(mx, dm[i][m]);
  cout << mx << endl;
}
