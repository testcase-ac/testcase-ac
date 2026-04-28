#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int square(int x, int y) {
  return (x / 3) * 3 + (y / 3);
}

char board[10][10];

void print_board() {
  for (int i = 0; i < 9; i++) cout << board[i] << '\n';
}

bool k_able_row(int i, char k) {
  bool able = true;
  for (int j = 0; j < 9; j++) able &= (board[i][j] != k);
  return able;
}

bool k_able_col(int j, char k) {
  bool able = true;
  for (int i = 0; i < 9; i++) able &= (board[i][j] != k);
  return able;
}

bool k_able_sqr(int s, char k) {
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

  if (board[i][j] != '0') j == 8 ? dfs(i + 1, 0) : dfs(i, j + 1);
  else {
    for (int k = '1'; k <= '9'; k++) {
      if (k_able_row(i, k) && k_able_col(j, k) && k_able_sqr(square(i, j), k)) {
        board[i][j] = k;
        j == 8 ? dfs(i + 1, 0) : dfs(i, j + 1);
        board[i][j] = '0';
      }
    }
  }
}

int main() {
  fast_io();

  for (int i = 0; i < 9; i++) cin >> board[i];
  dfs(0, 0);
}
