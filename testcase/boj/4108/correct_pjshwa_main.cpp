#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[105][105];

int main() {
  fast_io();

  while (1) {
    int n, m;
    cin >> n >> m;
    if (n == 0 && m == 0) break;

    memset(board, 0, sizeof(board));

    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 1; j <= m; j++) board[i + 1][j] = s[j - 1];
    }

    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
      if (board[i][j] == '*') continue;

      int cnt = 0;
      for (int k = j - 1; k <= j + 1; k++) if (board[i - 1][k] == '*') cnt++;
      for (int k = j - 1; k <= j + 1; k++) if (board[i + 1][k] == '*') cnt++;
      if (board[i][j - 1] == '*') cnt++;
      if (board[i][j + 1] == '*') cnt++;

      board[i][j] = cnt + 48;
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) cout << board[i][j];
      cout << '\n';
    }
  }

}
