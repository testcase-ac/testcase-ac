#include <bits/stdc++.h>
using namespace std;

char board[30000][31];

// Keep track of falling paths
stack<pair<int, int>> lastpos[30];
int r, c;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void next_pos(int col) {
  int cur_row, cur_col;
  tie(cur_row, cur_col) = lastpos[col].top();

  while (board[cur_row][cur_col] == 'O') {
    lastpos[col].pop();
    tie(cur_row, cur_col) = lastpos[col].top();
  }

  while (1) {
    lastpos[col].push({ cur_row, cur_col });

    // If the square under the rock is a wall or if the rock is in the bottom row of a column,
    // then the rock remains there.
    if (cur_row == r - 1 || board[cur_row + 1][cur_col] == 'X') break;

    // If the square under the rock contains another rock, then the falling rock may slide sideways: 
    if (board[cur_row + 1][cur_col] == 'O') {
      // If the squares left and left-down of the rock are empty, then the rock slides one square left. 
      if (cur_col > 0 && board[cur_row][cur_col - 1] == '.' && board[cur_row + 1][cur_col - 1] == '.') {
        cur_col--;
        cur_row++;
      }

      // If the rock doesn't slide left and the squares to the right and right-down are empty,
      // then the rock slides one square right.
      else if (cur_col < c - 1 && board[cur_row][cur_col + 1] == '.' && board[cur_row + 1][cur_col + 1] == '.') {
        cur_col++;
        cur_row++;
      }

      // Otherwise, the rock remains there and never moves again. 
      else break;
    }

    // If the square under the rock is empty, then the rock moves to that square.
    else cur_row++;
  }

  board[cur_row][cur_col] = 'O';
}

int main() {
  fast_io();

  cin >> r >> c;
  for (int i = 0; i < r; i++) cin >> board[i];
  for (int i = 0; i < c; i++) lastpos[i].push({ 0, i });

  int n, k;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> k;
    next_pos(k - 1);
  }

  for (int i = 0; i < r; i++) {
    cout << board[i] << '\n';
  }
}
