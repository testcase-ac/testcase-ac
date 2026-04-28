#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1}, dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
int board[MAX + 10][MAX + 10], vis[MAX + 10][MAX + 10];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> board[i][j];

  queue<pii> q;

  for (int j = 1; j <= M; j++) vis[0][j] = 1, q.push({0, j});
  for (int i = 1; i <= N; i++) vis[i][M + 1] = 1, q.push({i, M + 1});
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    for (int k = 0; k < 8; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
      if (board[nx][ny] == 0 || vis[nx][ny]) continue;
      vis[nx][ny] = 1;
      q.push({nx, ny});
    }
  }

  for (int j = 1; j <= M; j++) vis[N + 1][j] = 2, q.push({N + 1, j});
  for (int i = 1; i <= N; i++) vis[i][0] = 2, q.push({i, 0});

  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    for (int k = 0; k < 8; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
      if (board[nx][ny] == 0) continue;
      if (vis[nx][ny] == 1) return cout << "0\n", void();
      if (vis[nx][ny] == 2) continue;

      vis[nx][ny] = 2;
      q.push({nx, ny});
    }
  }

  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    if (i == 1 && j == 1) continue;
    if (i == N && j == M) continue;

    bool f1 = false, f2 = false;
    for (int k = 0; k < 8; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (vis[nx][ny] == 1) f1 = true;
      if (vis[nx][ny] == 2) f2 = true;
    }
    if (f1 && f2) return cout << "1\n", void();
  }

  cout << "2\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
