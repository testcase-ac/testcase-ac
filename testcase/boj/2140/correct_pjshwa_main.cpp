#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
const int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1}, dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  auto oob = [&](int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= N;
  };
  auto on_edge = [&](int x, int y) {
    return x == 0 || x == N - 1 || y == 0 || y == N - 1;
  };
  auto dec_edges = [&](int x, int y) {
    for (int k = 0; k < 8; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (oob(nx, ny) || !on_edge(nx, ny)) continue;
      assert(board[nx][ny] > '0');
      --board[nx][ny];
    }
  };
  auto print_board = [&]() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) cout << board[i][j];
      cout << '\n';
    }
    cout << "-----\n";
  };

  int inner = max(N - 4, 0);
  int ans = inner * inner;

  for (int j = 1; j < N - 1; ++j) {
    int i = 1;
    int t = board[i - 1][j - 1] - '0';
    if (t) ++ans, dec_edges(i, j);
  }
  for (int i = 2; i < N - 1; ++i) {
    int j = 1;
    int t = board[i - 1][j - 1] - '0';
    if (t) ++ans, dec_edges(i, j);
  }
  for (int i = 2; i < N - 1; ++i) {
    int j = N - 2;
    int t = board[i - 1][j + 1] - '0';
    if (t) ++ans, dec_edges(i, j);
  }
  for (int j = 2; j < N - 2; ++j) {
    int i = N - 2;
    int t = board[i + 1][j - 1] - '0';
    if (t) ++ans, dec_edges(i, j);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
