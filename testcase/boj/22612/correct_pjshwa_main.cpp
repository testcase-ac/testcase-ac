#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx1[4] = {0, 1, 0, -1}, dy1[4] = {1, 0, -1, 0};
const int dx2[4] = {0, 1, 0, -1}, dy2[4] = {-1, 0, 1, 0};
char board1[MAX + 1][MAX + 1], board2[MAX + 1][MAX + 1];
bool vis[MAX][MAX][MAX][MAX];
int N, M;

void solve() {
  string B1, B2;
  for (int i = 0; i < N; i++) {
    cin >> B1 >> B2;
    for (int j = 0; j < M; j++) {
      board1[i][j] = B1[j];
      board2[i][j] = B2[j];
    }
  }

  int sx1, sy1, sx2, sy2, ex1, ey1, ex2, ey2;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board1[i][j] == 'L') sx1 = i, sy1 = j;
    if (board1[i][j] == '%') ex1 = i, ey1 = j;
    if (board2[i][j] == 'R') sx2 = i, sy2 = j;
    if (board2[i][j] == '%') ex2 = i, ey2 = j;
  }

  memset(vis, 0, sizeof(vis));

  queue<tuple<int, int, int, int>> q;
  q.push({sx1, sy1, sx2, sy2});
  vis[sx1][sy1][sx2][sy2] = true;

  while (!q.empty()) {
    auto [x1, y1, x2, y2] = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nx1 = x1 + dx1[i], ny1 = y1 + dy1[i], nx2 = x2 + dx2[i], ny2 = y2 + dy2[i];
      bool oob1 = nx1 < 0 || nx1 >= N || ny1 < 0 || ny1 >= M;
      bool oob2 = nx2 < 0 || nx2 >= N || ny2 < 0 || ny2 >= M;

      if (oob1) nx1 = x1, ny1 = y1;
      if (oob2) nx2 = x2, ny2 = y2;
      if (board1[nx1][ny1] == '#') nx1 = x1, ny1 = y1;
      if (board2[nx2][ny2] == '#') nx2 = x2, ny2 = y2;

      bool reach1 = nx1 == ex1 && ny1 == ey1;
      bool reach2 = nx2 == ex2 && ny2 == ey2;
      if (reach1 && reach2) {
        cout << "Yes\n";
        return;
      }
      else if (reach1 || reach2) continue;

      if (vis[nx1][ny1][nx2][ny2]) continue;
      q.push({nx1, ny1, nx2, ny2});
      vis[nx1][ny1][nx2][ny2] = true;
    }
  }

  cout << "No\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> M >> N;
    if (N == 0 && M == 0) break;
    solve();
  }
}
