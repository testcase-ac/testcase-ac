#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int cdist[4][MAX][MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  int si, sj, ei, ej;
  for (int i = 0; i < N; ++i)   for (int j = 0; j < M; ++j) {
    if (board[i][j] == 'S') si = i, sj = j;
    if (board[i][j] == 'E') ei = i, ej = j;
  }

  memset(cdist, 0x3f, sizeof(cdist));
  queue<tuple<int, int, int>> q;
  for (int k = 0; k < 4; ++k) {
    cdist[k][si][sj] = 0;
    q.emplace(k, si, sj);
  }

  while (!q.empty()) {
    auto [d, i, j] = q.front(); q.pop();

    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == '#') continue;
      if (k == (d + 1) % 4) continue;

      if (cdist[k][ni][nj] > cdist[d][i][j] + 1) {
        cdist[k][ni][nj] = cdist[d][i][j] + 1;
        q.emplace(k, ni, nj);
      }
    }
  }

  int ans = INF;
  for (int k = 0; k < 4; ++k) ans = min(ans, cdist[k][ei][ej]);
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
