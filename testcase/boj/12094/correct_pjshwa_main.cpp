#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int pw2[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
int oboard[20][20], board[20][20], n;
int bcache[11][20][20], q[20];

void moveLeft() {
  for (int i = 0; i < n; i++) {
    int qi = 0;
    for (int j = 0; j < n; j++) {
      if (board[i][j]) q[qi++] = board[i][j];
      board[i][j] = 0;
    }
    for (int j = 0; j < qi; j++) {
      board[i][j] = q[j];
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
    int qi = 0;
    for (int j = n - 1; j >= 0; j--) {
      if (board[i][j]) q[qi++] = board[i][j];
      board[i][j] = 0;
    }
    for (int j = 0; j < qi; j++) {
      board[i][n - 1 - j] = q[j];
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
    int qi = 0;
    for (int i = 0; i < n; i++) {
      if (board[i][j]) q[qi++] = board[i][j];
      board[i][j] = 0;
    }
    for (int i = 0; i < qi; i++) {
      board[i][j] = q[i];
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
    int qi = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (board[i][j]) q[qi++] = board[i][j];
      board[i][j] = 0;
    }
    for (int i = 0; i < qi; i++) {
      board[n - 1 - i][j] = q[i];
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
void dfs(int i) {
  if (i == 10) {
    ans = max(ans, maxValue());
    return;
  }

  int maxv = maxValue(), rem = 10 - i;
  if (maxv * pw2[rem] <= ans) return;

  for (int d = 0; d < 4; d++) {
    copy(i);
    doSwipe(d);
    paste(i + 1);

    if (!identical(i)) dfs(i + 1);
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> bcache[0][i][j];
    ans = max(ans, bcache[0][i][j]);
  }

  copy(0);
  dfs(0);
  cout << ans << '\n';
}
