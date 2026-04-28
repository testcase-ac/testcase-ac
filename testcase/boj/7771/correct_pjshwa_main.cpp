#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int bi, bj;
  for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) {
    int x; cin >> x;
    if (x == 100) bi = i, bj = j;
  }

  char board[10][11]{};
  for (int i = 0; i < 10; ++i) fill(board[i], board[i] + 10, '.');

  int z = 1;
  for (int si = (bi & 1) ? 1 : 0; si < 10; si += 2) {
    if (si == bi) {
      int sj = max(0, bj - 3);
      for (int j = sj; j < sj + 4; ++j) board[si][j] = '#';
    }
    else if (z < 4) {
      int rep = 5 - z, j = 0;
      while (rep--) {
        for (int l = 0; l < z; ++l) board[si][j++] = '#';
        ++j;
      }
      ++z;
    }
  }

  for (int i = 0; i < 10; ++i) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
