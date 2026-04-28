#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, INF = 0x3f3f3f3f;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int A[MAXN][MAXN], cdist[MAXN][MAXN][3];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  deque<tuple<int, int, int>> q;
  memset(cdist, 0x3f, sizeof(cdist));
  if (A[0][0] <= 13) {
    q.emplace_back(0, 0, 0);
    cdist[0][0][0] = 1;
  }

  while (!q.empty()) {
    auto [i, j, t] = q.front(); q.pop_front();
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      bool vow = A[ni][nj] > 13;
      if (t == 0) {
        if (cdist[ni][nj][1] == INF && vow) {
          cdist[ni][nj][1] = cdist[i][j][0];
          q.emplace_front(ni, nj, 1);
        }
      }
      if (t == 1) {
        if (cdist[ni][nj][2] == INF && !vow) {
          cdist[ni][nj][2] = cdist[i][j][1];
          q.emplace_front(ni, nj, 2);
        }
        if (cdist[ni][nj][0] == INF && !vow) {
          cdist[ni][nj][0] = cdist[i][j][1] + 1;
          q.emplace_back(ni, nj, 0);
        }
      }
      if (t == 2) {
        if (cdist[ni][nj][0] == INF && !vow) {
          cdist[ni][nj][0] = cdist[i][j][2] + 1;
          q.emplace_back(ni, nj, 0);
        }
      }
    }
  }

  int ans = min(cdist[N - 1][M - 1][1], cdist[N - 1][M - 1][2]);
  if (ans == INF) cout << "BAD\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
