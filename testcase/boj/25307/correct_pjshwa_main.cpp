#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000, INF = 1e9 + 7;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int board[MAX][MAX], cdist[MAX][MAX];
bool goal[MAX][MAX];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  memset(cdist, -1, sizeof(cdist));

  int si, sj;

  queue<tii> mbfs;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> board[i][j];
    if (board[i][j] == 2) goal[i][j] = 1, board[i][j] = 0;
    if (board[i][j] == 4) si = i, sj = j, board[i][j] = 0;

    if (board[i][j] == 3) {
      mbfs.push({i, j, 0});
      cdist[i][j] = 0;
      board[i][j] = 0;
    }
  }

  while (!mbfs.empty()) {
    auto [i, j, c] = mbfs.front();
    mbfs.pop();

    cdist[i][j] = c;

    for (int l = 0; l < 4; l++) {
      int ni = i + dx[l], nj = j + dy[l];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (cdist[ni][nj] == -1 || cdist[ni][nj] > c + 1) {
        cdist[ni][nj] = c + 1;
        mbfs.push({ni, nj, c + 1});
      }
    }
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (cdist[i][j] != -1 && cdist[i][j] <= k) board[i][j] = 1;
  }
  memset(cdist, -1, sizeof(cdist));

  mbfs.push({si, sj, 0});
  cdist[si][sj] = 0;

  while (!mbfs.empty()) {
    auto [i, j, c] = mbfs.front();
    mbfs.pop();

    cdist[i][j] = c;

    for (int l = 0; l < 4; l++) {
      int ni = i + dx[l], nj = j + dy[l];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (board[ni][nj] == 1) continue;
      if (cdist[ni][nj] == -1 || cdist[ni][nj] > c + 1) {
        cdist[ni][nj] = c + 1;
        mbfs.push({ni, nj, c + 1});
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (goal[i][j] && cdist[i][j] != -1) ans = min(ans, cdist[i][j]);
  }

  if (ans == INF) cout << -1 << '\n';
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
