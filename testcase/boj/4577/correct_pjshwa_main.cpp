#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[20][20];
int r, c, cr, cc;

void swipeLeft() {
  if (board[cr][cc - 1] == '.') {
    board[cr][cc - 1] = 'w';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cc--;
  }
  else if (board[cr][cc - 1] == '+') {
    board[cr][cc - 1] = 'W';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cc--;
  }
  else if (board[cr][cc - 1] == 'B' || board[cr][cc - 1] == 'b') {
    if (board[cr][cc - 2] == '.') {
      board[cr][cc - 2] = 'b';
      board[cr][cc - 1] = board[cr][cc - 1] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cc--;
    }
    else if (board[cr][cc - 2] == '+') {
      board[cr][cc - 2] = 'B';
      board[cr][cc - 1] = board[cr][cc - 1] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cc--;
    }
  }
}

void swipeRight() {
  if (board[cr][cc + 1] == '.') {
    board[cr][cc + 1] = 'w';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cc++;
  }
  else if (board[cr][cc + 1] == '+') {
    board[cr][cc + 1] = 'W';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cc++;
  }
  else if (board[cr][cc + 1] == 'B' || board[cr][cc + 1] == 'b') {
    if (board[cr][cc + 2] == '.') {
      board[cr][cc + 2] = 'b';
      board[cr][cc + 1] = board[cr][cc + 1] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cc++;
    }
    else if (board[cr][cc + 2] == '+') {
      board[cr][cc + 2] = 'B';
      board[cr][cc + 1] = board[cr][cc + 1] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cc++;
    }
  }
}

void swipeUp() {
  if (board[cr - 1][cc] == '.') {
    board[cr - 1][cc] = 'w';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cr--;
  }
  else if (board[cr - 1][cc] == '+') {
    board[cr - 1][cc] = 'W';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cr--;
  }
  else if (board[cr - 1][cc] == 'B' || board[cr - 1][cc] == 'b') {
    if (board[cr - 2][cc] == '.') {
      board[cr - 2][cc] = 'b';
      board[cr - 1][cc] = board[cr - 1][cc] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cr--;
    }
    else if (board[cr - 2][cc] == '+') {
      board[cr - 2][cc] = 'B';
      board[cr - 1][cc] = board[cr - 1][cc] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cr--;
    }
  }
}

void swipeDown() {
  if (board[cr + 1][cc] == '.') {
    board[cr + 1][cc] = 'w';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cr++;
  }
  else if (board[cr + 1][cc] == '+') {
    board[cr + 1][cc] = 'W';
    board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
    cr++;
  }
  else if (board[cr + 1][cc] == 'B' || board[cr + 1][cc] == 'b') {
    if (board[cr + 2][cc] == '.') {
      board[cr + 2][cc] = 'b';
      board[cr + 1][cc] = board[cr + 1][cc] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cr++;
    }
    else if (board[cr + 2][cc] == '+') {
      board[cr + 2][cc] = 'B';
      board[cr + 1][cc] = board[cr + 1][cc] == 'B' ? 'W' : 'w';
      board[cr][cc] = board[cr][cc] == 'W' ? '+' : '.';
      cr++;
    }
  }
}

void printBoard() {
  for (int i = 0; i < r; i++) cout << board[i] << '\n';
}

bool finished() {
  bool ret = true;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) ret &= (board[i][j] != 'b');
  }
  return ret;
}

bool playGame(string& instrs) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (board[i][j] == 'w' || board[i][j] == 'W') {
        cr = i;
        cc = j;
        break;
      }
    }
  }

  for (char inst : instrs) {
    if (inst == 'U') swipeUp();
    if (inst == 'D') swipeDown();
    if (inst == 'L') swipeLeft();
    if (inst == 'R') swipeRight();

    if (finished()) return true;
  }

  return false;
}

int main() {
  fast_io();

  int tc = 0;
  string instrs;
  while (1) {
    cin >> r >> c;
    if (r == 0 && c == 0) break;

    for (int i = 0; i < r; i++) cin >> board[i];
    cin >> instrs;

    bool result = playGame(instrs);
    cout << "Game " << ++tc << ": " << (result ? "complete" : "incomplete") << '\n';
    printBoard();
  }

}
