#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[2001][2000];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i > 0) board[i - 1][j] = board[i - 1][j] == 'W' ? 'B' : 'W';
      if (i < n - 1) board[i + 1][j] = board[i + 1][j] == 'W' ? 'B' : 'W';
      if (j > 0) board[i][j - 1] = board[i][j - 1] == 'W' ? 'B' : 'W';
      if (j < m - 1) board[i][j + 1] = board[i][j + 1] == 'W' ? 'B' : 'W';
    }
  }

  cout << "1\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] == 'B') cout << '3';
      else cout << '2';
    }
    cout << '\n';
  }
}
