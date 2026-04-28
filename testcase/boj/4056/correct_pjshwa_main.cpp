#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int square(int x, int y) {
  return (x / 3) * 3 + (y / 3);
}

char board[10][10];
bool solved, invalid;

void print_board() {
  for (int i = 0; i < 9; i++) cout << board[i] << '\n';
}

bool check_validity() {
  int s;

  for (int i = 0; i < 9; i++) {
    s = 0;
    for (int j = 0; j < 9; j++) s += (board[i][j] - '0');
    if (s != 45) return false;
  }

  for (int j = 0; j < 9; j++) {
    s = 0;
    for (int i = 0; i < 9; i++) s += (board[i][j] - '0');
    if (s != 45) return false;
  }

  for (int k = 0; k < 9; k++) {
    s = 0;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) s += (board[(k / 3) * 3 + i][(k % 3) * 3 + j] - '0');
    if (s != 45) return false;
  }

  return true;
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
  if (solved) return;

  if (i == 9 && j == 0) {
    if (check_validity()) print_board();
    else invalid = true;

    solved = true;
    return;
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

  int t;
  cin >> t;
  while (t--) {
    solved = invalid = false;
    for (int i = 0; i < 9; i++) cin >> board[i];
    dfs(0, 0);

    if (!solved || invalid) cout << "Could not complete this grid.\n";
    cout << '\n';
  }

}
