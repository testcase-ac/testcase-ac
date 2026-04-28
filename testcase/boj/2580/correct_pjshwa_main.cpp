#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int square(int x, int y) {
  return (x / 3) * 3 + (y / 3);
}

int board[9][9];

void print_board() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) cout << board[i][j] << ' ';
    cout << '\n';
  }
}

bool k_able_row(int i, int k) {
  bool able = true;
  for (int j = 0; j < 9; j++) able &= (board[i][j] != k);
  return able;
}

bool k_able_col(int j, int k) {
  bool able = true;
  for (int i = 0; i < 9; i++) able &= (board[i][j] != k);
  return able;
}

bool k_able_sqr(int s, int k) {
  bool able = true;
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    able &= (board[(s / 3) * 3 + i][(s % 3) * 3 + j] != k);
  }
  return able;
}

void dfs(int i, int j) {
  if (i == 9 && j == 0) {
    print_board();
    exit(0);
  }

  if (board[i][j]) j == 8 ? dfs(i + 1, 0) : dfs(i, j + 1);
  else {
    for (int k = 1; k <= 9; k++) {
      if (k_able_row(i, k) && k_able_col(j, k) && k_able_sqr(square(i, j), k)) {
        board[i][j] = k;
        j == 8 ? dfs(i + 1, 0) : dfs(i, j + 1);
        board[i][j] = 0;
      }
    }
  }
}

int main() {
  fast_io();

  for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) cin >> board[i][j];
  dfs(0, 0);
}
