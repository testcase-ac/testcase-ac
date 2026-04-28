#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int oboard[20][20], board[20][20], n;

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

void initBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) board[i][j] = oboard[i][j];
  }
}

int main() {
  fast_io();

  int t;
  cin >> t;

  for (int tc = 1; tc <= t; tc++) {

    string dir;

    cin >> n >> dir;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) cin >> oboard[i][j];
    }

    initBoard();
    if (dir == "left") swipeLeft();
    if (dir == "right") swipeRight();
    if (dir == "up") swipeUp();
    if (dir == "down") swipeDown();

    cout << "Case #" << tc << ":\n";
    printBoard();

  }

}
