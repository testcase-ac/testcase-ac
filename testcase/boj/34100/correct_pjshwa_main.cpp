#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000;
char board[MAXN + 1][MAXN + 1];
int N, M;

bool could_place_L(int r, int c) {
  if (r == 0 || c == M - 1) return false;
  if (board[r][c] != '.' || board[r - 1][c] != '.' || board[r][c + 1] != '.') return false;
  return true;
}

bool could_place_R(int r, int c) {
  if (r == 0 || c == M - 1) return false;
  if (board[r][c] != '.' || board[r - 1][c + 1] != '.' || board[r][c + 1] != '.') return false;
  return true;
}

void place_L(int r, int c) {
  board[r][c] = 'a';
  board[r - 1][c] = 'a';
  board[r][c + 1] = 'a';
}

void place_R(int r, int c) {
  board[r][c] = 'b';
  board[r - 1][c + 1] = 'b';
  board[r][c + 1] = 'b';
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  for (int j = 0; j < M; ++j) for (int i = N - 1; i >= 1; --i) {
    if (board[i][j] != '.') continue;
    if (could_place_L(i, j)) place_L(i, j);
    else if (could_place_R(i, j)) place_R(i, j);
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '.') return cout << "-1\n", void();
  }
  for (int i = 0; i < N; ++i) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
