#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int oboard[20][20], board[20][20], n;

void moveLeft() {
  for (int i = 0; i < n; i++) {
    queue<int> q;
    for (int j = 0; j < n; j++) {
      if (board[i][j]) q.push(board[i][j]);
      board[i][j] = 0;
    }
    for (int j = 0; j < n; j++) {
      if (q.empty()) break;
      board[i][j] = q.front();
      q.pop();
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
    queue<int> q;
    for (int j = n - 1; j >= 0; j--) {
      if (board[i][j]) q.push(board[i][j]);
      board[i][j] = 0;
    }
    for (int j = n - 1; j >= 0; j--) {
      if (q.empty()) break;
      board[i][j] = q.front();
      q.pop();
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
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (board[i][j]) q.push(board[i][j]);
      board[i][j] = 0;
    }
    for (int i = 0; i < n; i++) {
      if (q.empty()) break;
      board[i][j] = q.front();
      q.pop();
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
    queue<int> q;
    for (int i = n - 1; i >= 0; i--) {
      if (board[i][j]) q.push(board[i][j]);
      board[i][j] = 0;
    }
    for (int i = n - 1; i >= 0; i--) {
      if (q.empty()) break;
      board[i][j] = q.front();
      q.pop();
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

int c[5] = {0, 0, 0, 0, 0};

bool finished() {
  return c[0] == 3 && c[1] == 3 && c[2] == 3 && c[3] == 3 && c[4] == 3;
}

void inc() {
  c[4]++;
  if (c[4] == 4) {c[4] = 0; c[3]++;}
  if (c[3] == 4) {c[3] = 0; c[2]++;}
  if (c[2] == 4) {c[2] = 0; c[1]++;}
  if (c[1] == 4) {c[1] = 0; c[0]++;}
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

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> oboard[i][j];
  }

  int mv = 0;
  while (1) {
    initBoard();
    for (int i = 0; i < 5; i++) doSwipe(c[i]);
    mv = max(mv, findMax());
    if (finished()) break;
    inc();
  }

  cout << mv;
}
