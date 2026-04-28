#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int board[30][30];

void announce_win(int i, int j, int p) {
  cout << p << '\n' << i << ' ' << j;
  exit(0);
}

void check_win(int i, int j, int p) {
  bool row = 1, col = 1, diagr = 1, diagl = 1;
  for (int k = -2; k <= 2; k++) {
    row &= board[i + k][j] == p;
    col &= board[i][j + k] == p;
    diagr &= board[i + k][j + k] == p;
    diagl &= board[i + k][j - k] == p;
  }
  row &= (board[i - 3][j] != p && board[i + 3][j] != p);
  col &= (board[i][j - 3] != p && board[i][j + 3] != p);
  diagr &= (board[i - 3][j - 3] != p && board[i + 3][j + 3] != p);
  diagl &= (board[i - 3][j + 3] != p && board[i + 3][j - 3] != p);

  if (row) announce_win(i - 6, j - 4, p);
  if (col) announce_win(i - 4, j - 6, p);
  if (diagr) announce_win(i - 6, j - 6, p);
  if (diagl) announce_win(i - 2, j - 6, p);
}

int main() {
  fast_io();

  for (int i = 5; i < 24; i++) for (int j = 5; j < 24; j++) cin >> board[i][j];
  for (int i = 5; i < 24; i++) for (int j = 5; j < 24; j++) check_win(i, j, 1), check_win(i, j, 2);
  cout << 0;
}
