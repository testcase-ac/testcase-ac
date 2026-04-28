#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300;
char board[MAX + 1][MAX + 1];

void erase_f(int i, int j) {
  board[i][j] = board[i][j - 1] = board[i + 2][j - 1] = '.';
  for (int k = 0; k < 5; k++) board[i + k][j - 2] = '.';
}

void erase_q(int i, int j) {
  for (int k = 0; k < 5; k++) board[i + k][j] = '.';
  board[i][j - 1] = board[i + 2][j - 1] = '.';
  for (int k = 0; k < 3; k++) board[i + k][j - 2] = '.';
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int qcnt = 0, fcnt = 0;
  for (int j = m - 1; j >= 0; j--) {
    for (int i = 0; i < n - 1; i++) {
      if (board[i][j] == '.') continue;

      if (board[i + 1][j] == '#') qcnt++, erase_q(i, j);
      else fcnt++, erase_f(i, j);
    }
  }
  cout << qcnt << ' ' << fcnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
