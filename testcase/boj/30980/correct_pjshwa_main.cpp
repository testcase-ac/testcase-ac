#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];

void mark_correct_5(int si, int sj) {
  for (int j = sj; j < sj + 5; ++j) {
    board[si - 1][j] = '*';
    board[si + 1][j] = '*';
  }
  board[si][sj - 1] = board[si][sj + 5] = '*';
}

void mark_correct_6(int si, int sj) {
  for (int j = sj; j < sj + 6; ++j) {
    board[si - 1][j] = '*';
    board[si + 1][j] = '*';
  }
  board[si][sj - 1] = board[si][sj + 6] = '*';
}

void mark_incorrect(int si, int sj) {
  board[si - 1][sj + 2] = '/';
  board[si][sj + 1] = '/';
  board[si + 1][sj] = '/';
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < 3 * N; ++i) cin >> board[i];

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int si = 3 * i + 1, sj = 8 * j + 1;
    int a = board[si][sj] - '0';
    int b = board[si][sj + 2] - '0';
    int c = board[si][sj + 4] - '0';
    if (board[si][sj + 5] != '.') {
      c = c * 10 + board[si][sj + 5] - '0';
    }

    if (a + b == c) {
      if (c < 10) mark_correct_5(si, sj);
      else mark_correct_6(si, sj);
    }
    else mark_incorrect(si, sj);
  }

  for (int i = 0; i < 3 * N; ++i) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
