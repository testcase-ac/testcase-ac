#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];

void solve() {
  int r, c, rr, cr, rb, cb; cin >> r >> c >> rr >> cr >> rb >> cb;
  if ((r * c) & 1) return cout << "IMPOSSIBLE\n", void();

  memset(board, 0, sizeof(board));

  rr--, cr--, rb--, cb--;
  board[rr][cr] = 'R'; board[rb][cb] = 'B';
  board[r - 1 - rr][c - 1 - cr] = 'B'; board[r - 1 - rb][c - 1 - cb] = 'R';

  int rcnt = (r * c - 1) / 2;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    if (rcnt == 0 || board[i][j]) continue;

    board[i][j] = 'R';
    board[r - 1 - i][c - 1 - j] = 'B';
  }

  for (int i = 0; i < r; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
