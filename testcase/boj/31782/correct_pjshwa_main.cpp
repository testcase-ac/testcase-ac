#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAXN + 1][MAXN + 1];
int indegree[MAXN][MAXN], vis[MAXN][MAXN];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; ++i) cin >> board[i];

  queue<pii> Q;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == 'O') Q.emplace(i, j);
  }

  while (!Q.empty()) {
    auto [i, j] = Q.front(); Q.pop();
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (++indegree[ni][nj] >= 2 && board[ni][nj] == '.') {
        board[ni][nj] = 'O';
        Q.emplace(ni, nj);
      }
    }
  }

  // groups of 'O' always form a rectangle.
  int ans = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '.' || vis[i][j]) continue;

    int mini = i, maxi = i, minj = j, maxj = j;
    Q.emplace(i, j); vis[i][j] = 1;
    while (!Q.empty()) {
      auto [x, y] = Q.front(); Q.pop();
      mini = min(mini, x); maxi = max(maxi, x);
      minj = min(minj, y); maxj = max(maxj, y);
      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (vis[nx][ny] || board[nx][ny] == '.') continue;
        Q.emplace(nx, ny); vis[nx][ny] = 1;
      }
    }

    int di = maxi - mini + 1, dj = maxj - minj + 1;
    if (di > K && dj > K) ans += di * dj;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
