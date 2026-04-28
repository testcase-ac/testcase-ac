#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[5][10001];

int main() {
  fast_io();

  int n;
  for (int i = 0; i < 5; i++) cin >> board[i];
  for (int i = 0; i <= 10000; i++) {
    if (board[0][i] == 0) {
      n = i;
      break;
    }
  }

  for (int i = 0; i < n; i++) {
    if (board[1][i] == '.') continue;
    if (board[1][i] == 'w') {
      board[0][i] = '.';
      board[1][i] = 'o';
      board[2][i] = 'm';
      board[3][i] = 'l';
      board[4][i] = 'n';
    }
    else if (board[1][i] == 'o') {
      board[0][i] = 'o';
      board[1][i] = 'w';
      board[2][i] = 'l';
      board[3][i] = 'n';
      board[4][i] = '.';
    }
  }

  for (int i = 0; i < 5; i++) cout << board[i] << '\n';
}
