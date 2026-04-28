#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];

bool is_blue(int i, int j) {
  bool ret = true;
  for (int di = 0; di <= 1; di++) for (int dj = 0; dj <= 1; dj++) {
    ret &= board[i + di][j + dj] == '#';
  }
  return ret;
}

void print_red(int i, int j) {
  board[i][j] = '/';
  board[i + 1][j] = '\\';
  board[i][j + 1] = '\\';
  board[i + 1][j + 1] = '/';
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ":\n";

  int R, C; cin >> R >> C;
  for (int i = 0; i < R; i++) cin >> board[i];

  for (int i = 0; i < R - 1; i++) for (int j = 0; j < C - 1; j++) {
    if (is_blue(i, j)) print_red(i, j);
  }

  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    if (board[i][j] == '#') return cout << "Impossible\n", void();
  }
  for (int i = 0; i < R; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
