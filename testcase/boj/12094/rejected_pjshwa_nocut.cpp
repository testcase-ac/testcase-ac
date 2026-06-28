#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int pw2[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
int oboard[20][20], board[20][20], n;
int bcache[11][20][20];

void moveLeft() {
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

void mergeLeft() {
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n; j++) {
      if (!board[i][j]) continue;
      if (board[i][j - 1] != board[i][j]) continue;

      board[i][j - 1] <<= 1;
      board[i][j] = 0;
    }
  }
}

void swipeLeft() {
  moveLeft();
  mergeLeft();
  moveLeft();
}

void moveRight() {
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

void mergeRight() {
  for (int i = 0; i < n; i++) {
    for (int j = n - 2; j >= 0; j--) {
      if (!board[i][j]) continue;
      if (board[i][j + 1] != board[i][j]) continue;

      board[i][j + 1] <<= 1;
      board[i][j] = 0;
    }
  }
}

void swipeRight() {
  moveRight();
  mergeRight();
  moveRight();
}

void moveUp() {
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

void mergeUp() {
  for (int j = 0; j < n; j++) {
    for (int i = 1; i < n; i++) {
      if (!board[i][j]) continue;
      if (board[i - 1][j] != board[i][j]) continue;

      board[i - 1][j] <<= 1;
      board[i][j] = 0;
    }
  }
}

void swipeUp() {
  moveUp();
  mergeUp();
  moveUp();
}

void moveDown() {
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

void mergeDown() {
  for (int j = 0; j < n; j++) {
    for (int i = n - 2; i >= 0; i--) {
      if (!board[i][j]) continue;
      if (board[i + 1][j] != board[i][j]) continue;

      board[i + 1][j] <<= 1;
      board[i][j] = 0;
    }
  }
}

void swipeDown() {
  moveDown();
  mergeDown();
  moveDown();
}

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << board[i][j] << ' ';
    cout << '\n';
  }
}

void doSwipe(int i) {
  if (i == 0) swipeLeft();
  if (i == 1) swipeRight();
  if (i == 2) swipeUp();
  if (i == 3) swipeDown();
}

int findMax() {
  int mv = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) mv = max(mv, board[i][j]);
  }
  return mv;
}

void copy(int l) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) board[i][j] = bcache[l][i][j];
  }
}

void paste(int l) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) bcache[l][i][j] = board[i][j];
  }
}

bool identical(int l) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) if (bcache[l + 1][i][j] != bcache[l][i][j]) return false;
  }
  return true;
}

int maxValue() {
  int mv = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) mv = max(mv, board[i][j]);
  }
  return mv;
}

int ans = 0;
void dfs(int i, int l) {
  if (i == 10) {
    ans = max(ans, findMax());
    return;
  }

  for (int d = 0; d < 4; d++) {
    copy(i);
    doSwipe(d);
    paste(i + 1);

    dfs(i + 1, d);
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> bcache[0][i][j];

  dfs(0, -1);
  cout << ans << '\n';
}
