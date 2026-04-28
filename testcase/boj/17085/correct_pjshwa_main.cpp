#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 15;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1 ,0};
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  int ans = 0;
  for (int si = 0; si < N; si++) for (int sj = 0; sj < M; sj++) {
    if (board[si][sj] != '#') continue;

    bool vis[N][M]{};
    vis[si][sj] = true;

    for (int ssz = 1;; ssz++) {
      int sscore = 1 + (ssz - 1) * 4;
      for (int ti = 0; ti < N; ti++) for (int tj = 0; tj < M; tj++) {
        if (board[ti][tj] != '#' || vis[ti][tj]) continue;

        for (int tsz = 1;; tsz++) {
          int tscore = 1 + (tsz - 1) * 4;
          ans = max(ans, sscore * tscore);

          bool f = true;
          for (int k = 0; k < 4; k++) {
            int ni = ti + dx[k] * tsz, nj = tj + dy[k] * tsz;
            if (ni < 0 || ni >= N || nj < 0 || nj >= M || board[ni][nj] != '#') f = false;
            if (vis[ni][nj]) f = false;
          }
          if (!f) break;
        }
      }

      bool f = true;
      for (int k = 0; k < 4; k++) {
        int ni = si + dx[k] * ssz, nj = sj + dy[k] * ssz;
        if (ni < 0 || ni >= N || nj < 0 || nj >= M || board[ni][nj] != '#') f = false;
      }
      if (!f) break;

      for (int k = 0; k < 4; k++) {
        int ni = si + dx[k] * ssz, nj = sj + dy[k] * ssz;
        vis[ni][nj] = true;
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
