#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
char board[MAX + 1][MAX + 1];
int cdist[MAX + 1][MAX + 1][11][2];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;
  for (int i = 0; i < N; ++i) cin >> board[i];

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j)
  for (int k = 0; k <= K; ++k) for (int l = 0; l < 2; ++l) cdist[i][j][k][l] = INF;

  queue<tuple<int, int, int, int>> q;
  cdist[0][0][0][0] = 1;
  q.emplace(0, 0, 0, 0);

  while (!q.empty()) {
    auto [x, y, w, l] = q.front(); q.pop();

    if (x == N - 1 && y == M - 1) {
      cout << cdist[x][y][w][l] << '\n';
      return;
    }

    if (cdist[x][y][w][1 - l] == INF) {
      cdist[x][y][w][1 - l] = cdist[x][y][w][l] + 1;
      q.emplace(x, y, w, 1 - l);
    }

    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

      if (board[nx][ny] == '0') {
        if (cdist[nx][ny][w][1 - l] == INF) {
          cdist[nx][ny][w][1 - l] = cdist[x][y][w][l] + 1;
          q.emplace(nx, ny, w, 1 - l);
        }
      }
      else {
        if (l == 0 && w < K && cdist[nx][ny][w + 1][1 - l] == INF) {
          cdist[nx][ny][w + 1][1 - l] = cdist[x][y][w][l] + 1;
          q.emplace(nx, ny, w + 1, 1 - l);
        }
      }
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
