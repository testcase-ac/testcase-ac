#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

char board[10][10];
bool B[9][9][10];

void throw_error() {
  cout << "GRESKA\n";
  exit(0);
}

int idx_square(int i, int j) {
  return (i / 3) * 3 + j / 3;
}

bool invalid_board() {
  for (int i = 0; i < 9; ++i) {
    int C[10]{};
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') continue;
      int num = board[i][j] - '0';
      if (C[num]) return true;
      C[num] = 1;
    }
  }

  for (int j = 0; j < 9; ++j) {
    int C[10]{};
    for (int i = 0; i < 9; ++i) {
      if (board[i][j] == '.') continue;
      int num = board[i][j] - '0';
      if (C[num]) return true;
      C[num] = 1;
    }
  }

  for (int q = 0; q < 9; ++q) {
    int C[10]{};
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
      int ni = 3 * (q / 3) + i;
      int nj = 3 * (q % 3) + j;
      if (board[ni][nj] == '.') continue;
      int num = board[ni][nj] - '0';
      if (C[num]) return true;
      C[num] = 1;
    }
  }

  return false;
}

void fill_B(int i, int j, int num) {
  for (int k = 1; k <= 9; ++k) B[i][j][k] = 1;
  for (int oj = 0; oj < 9; ++oj) B[i][oj][num] = 1;
  for (int oi = 0; oi < 9; ++oi) B[oi][j][num] = 1;
  int q = idx_square(i, j);
  for (int oi = 0; oi < 3; ++oi) for (int oj = 0; oj < 3; ++oj) {
    int ni = 3 * (q / 3) + oi;
    int nj = 3 * (q % 3) + oj;
    B[ni][nj][num] = 1;
  }
}

void solve() {
  for (int i = 0; i < 9; ++i) cin >> board[i];
  if (invalid_board()) return throw_error();

  queue<pii> Q;
  for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) {
    if (board[i][j] == '.') continue;
    fill_B(i, j, board[i][j] - '0');
    Q.push({i, j});
  }

  auto fill_if_applicable = [&](int num, int q) {
    int cnt = 0;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
      int ni = 3 * (q / 3) + i;
      int nj = 3 * (q % 3) + j;
      if (B[ni][nj][num]) ++cnt;
      if (board[ni][nj] - '0' == num) return;
    }
    if (cnt == 9) return throw_error();
    if (cnt != 8) return;

    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
      int ni = 3 * (q / 3) + i;
      int nj = 3 * (q % 3) + j;
      if (B[ni][nj][num]) continue;
      board[ni][nj] = num + '0';
      Q.push({ni, nj});
    }
  };

  while (!Q.empty()) {
    auto [i, j] = Q.front(); Q.pop();
    int num = board[i][j] - '0';
    fill_B(i, j, num);
    for (int num = 1; num <= 9; ++num) for (int q = 0; q < 9; ++q) {
      fill_if_applicable(num, q);
    }
  }

  for (int i = 0; i < 9; ++i) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
