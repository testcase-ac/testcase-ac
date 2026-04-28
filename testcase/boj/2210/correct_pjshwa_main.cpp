#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n = 5, board[5][5];
set<string> s;

void dfs(int i, int j, string c) {
  if (c.size() == 6) s.insert(c);
  else {
    if (i > 0) dfs(i - 1, j, c + to_string(board[i - 1][j]));
    if (i < n - 1) dfs(i + 1, j, c + to_string(board[i + 1][j]));
    if (j > 0) dfs(i, j - 1, c + to_string(board[i][j - 1]));
    if (j < n - 1) dfs(i, j + 1, c + to_string(board[i][j + 1]));
  }
}

int main() {
  fast_io();

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) dfs(i, j, to_string(board[i][j]));
  cout << s.size();
}
