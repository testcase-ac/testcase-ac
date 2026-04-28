#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 8;
int board[MAX][MAX], oboard[MAX][MAX], n;

void init() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) board[i][j] = oboard[i][j];
}

void flip_row(int i) {
  for (int j = 0; j < n; j++) board[i][j] = !board[i][j];
}

void flip_col(int j) {
  for (int i = 0; i < n; i++) board[i][j] = !board[i][j];
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> oboard[i][j];

  int mmoves = 1e9;
  for (int state = 0; state < (1 << (2 * n)); state++) {
    int moves = 0;
    init();

    for (int i = 0; i < n; i++) {
      if (state & (1 << i)) moves++, flip_row(i);
    }
    for (int j = 0; j < n; j++) {
      if (state & (1 << (n + j))) moves++, flip_col(j);
    }

    int bcnt = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
      if (board[i][j] == 0) bcnt++;
    }
    mmoves = min(mmoves, moves + min(bcnt, n * n - bcnt));
  }

  cout << mmoves << '\n';
}
