#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char oboard[11][11], board[11][11];
int n, m;

void move_left() {
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n; j++) {
      if (!board[i][j]) continue;
      int k = j;
      while (k > 0 && board[i][k - 1] == 0) k--;

      if (k != j) {
        board[i][k] = board[i][j];
        board[i][j] = 0;
      }
    }
  }
}

void move_right() {
  for (int i = 0; i < n; i++) {
    for (int j = n - 2; j >= 0; j--) {
      if (!board[i][j]) continue;
      int k = j;
      while (k < n - 1 && board[i][k + 1] == 0) k++;

      if (k != j) {
        board[i][k] = board[i][j];
        board[i][j] = 0;
      }
    }
  }
}

void move_up() {
  for (int j = 0; j < n; j++) {
    for (int i = 1; i < n; i++) {
      if (!board[i][j]) continue;
      int k = i;
      while (k > 0 && board[k - 1][j] == 0) k--;

      if (k != i) {
        board[k][j] = board[i][j];
        board[i][j] = 0;
      }
    }
  }
}

void move_down() {
  for (int j = 0; j < n; j++) {
    for (int i = n - 2; i >= 0; i--) {
      if (!board[i][j]) continue;
      int k = i;
      while (k < n - 1 && board[k + 1][j] == 0) k++;

      if (k != i) {
        board[k][j] = board[i][j];
        board[i][j] = 0;
      }
    }
  }
}

void print_board() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << board[i][j] << ' ';
    cout << '\n';
  }
}

void init_board() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) board[i][j] = oboard[i][j];
  }
}

int c[10] = {0, 0, 0, 0, 0};

bool finished() {
  bool f = true;
  for (int i = 0; i < 10; i++) f &= (c[i] == 3);
  return f;
}

void inc() {
  c[9]++;
  for (int i = 9; i >= 1; i--) {
    if (c[i] == 4) {
      c[i] = 0;
      c[i - 1]++;
    }
  }
}

void do_move(int i) {
  if (i == 0) move_left();
  if (i == 1) move_up();
  if (i == 2) move_right();
  if (i == 3) move_down();
}

int findMax() {
  int mv = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) mv = max(mv, board[i][j]);
  }
  return mv;
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> oboard[i];

  int mv = 0;
  while (1) {
    for (int i = 0; i < 9; i++) {
      if (c[i] == c[i + 1] || (c[i] + 2) % 4 == c[i + 1]) continue;
    }

    init_board();
    for (int i = 0; i < 10; i++) do_move(c[i]);
    mv = max(mv, findMax());
    if (finished()) break;
    inc();
  }

  cout << mv;
}
