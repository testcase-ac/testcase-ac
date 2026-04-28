#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 650;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
char W[MAXN][MAXN];

int N;
void solve() {
  N *= 2; int M = N + 1;
  for (int i = 0; i < N - 1; ++i) cin >> W[i];

  vector<vector<vector<int>>> B(N, vector<vector<int>>(M, vector<int>(2, 0)));
  for (int i = 0; i < N; i += 2) for (int j = 0; j < M - 1; ++j) {

    // blockage on right
    if (j & 1) {
      if (i > 0 && W[i - 1][j / 2] == 'V') B[i][j][0] = 1;
    }
    else {
      if (W[i][j / 2] == 'V') B[i][j][0] = 1;
    }

    // blockage on bottom
    if (W[i][j / 2] == 'H') B[i][j][1] = 1;
  }

  for (int i = 1; i < N; i += 2) for (int j = 0; j < M; ++j) {

    // blockage on right
    if (j & 1) {
      if (i < N - 1 && W[i][j / 2] == 'V') B[i][j][0] = 1;
    }
    else {
      if (i > 0 && W[i - 1][j / 2] == 'V') B[i][j][0] = 1;
    }

    // blockage on bottom
    if (i < N - 1 && j > 0 && W[i][(j - 1) / 2] == 'H') B[i][j][1] = 1;
  }

  // recreate board
  vector<vector<char>> board(2 * N, vector<char>(2 * M, '#'));

  for (int i = 0; i < N; ++i) {
    int bj = 0;
    for (int j = 0; j < M; ++j) {
      board[2 * i][bj++] = '.';
      board[2 * i][bj++] = (B[i][j][0] ? '#' : '.');
    }
    if (i == N - 1) break;

    bj = 0;
    for (int j = 0; j < M; ++j) {
      board[2 * i + 1][bj++] = (B[i][j][1] ? '#' : '.');
      board[2 * i + 1][bj++] = '#';
    }
  }

  // cout << "board =\n";
  // for (int i = 0; i < 2 * N; ++i) {
  //   for (int j = 0; j < 2 * M; ++j) cout << board[i][j];
  //   cout << '\n';
  // }

  vector<vector<bool>> vis(2 * N, vector<bool>(2 * M, false));
  auto oob = [&](int x, int y) {
    return x < 0 || x >= 2 * N || y < 0 || y >= 2 * M;
  };

  function<void(int, int)> dfs = [&](int x, int y) {
    vis[x][y] = true;
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d], ny = y + dy[d];
      if (oob(nx, ny) || vis[nx][ny] || board[nx][ny] == '#') continue;
      dfs(nx, ny);
    }
  };

  int cc = 0;
  for (int i = 0; i < 2 * N; ++i) for (int j = 0; j < 2 * M; ++j) {
    if (vis[i][j] || board[i][j] == '#') continue;
    dfs(i, j); ++cc;
  }
  cout << cc - 1 << '\n';
}

int main() {
  fast_io();

  while (cin >> N) solve();
}
