#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int board[MAX][MAX];
bool vis[MAX][MAX];
int ans;
int N, M;

void dfs(int i, int j, int w, int p, int acc) {
  if (p == 0) return;

  vis[i][j] = 1;
  acc += board[i][j];
  ans = max(ans, acc);

  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

    if (w == k) {
      if (p < 1) continue;
      if (!vis[ni][nj]) dfs(ni, nj, k, p - 1, acc);
    }
    else {
      if (p < 2) continue;
      if (!vis[ni][nj]) dfs(ni, nj, k, p - 2, acc);
    }
  }

  vis[i][j] = 0;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> board[i][j];

  int x, y, p;
  cin >> x >> y >> p;

  vis[x][y] = 1;
  ans = board[x][y];
  for (int k = 0; k < 4; k++) {
    int ni = x + dx[k], nj = y + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

    dfs(ni, nj, k, p, board[x][y]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
