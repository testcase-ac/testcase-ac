#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
const int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1}, dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
char board[MAX + 1][MAX + 1];
int cdist[MAX][MAX];

void solve() {
  int N, M; cin >> N >> M;

  int si, sj, ei, ej;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 'K') si = i, sj = j;
      if (board[i][j] == '*') ei = i, ej = j;
    }
  }

  memset(cdist, 0x3f, sizeof(cdist));
  deque<pii> dq;
  dq.push_back({si, sj}); cdist[si][sj] = 0;

  while (!dq.empty()) {
    auto [ci, cj] = dq.front(); dq.pop_front();
    if (ci == ei && cj == ej) {
      cout << cdist[ci][cj] << '\n';
      return;
    }

    for (int k = 0; k < 8; k++) {
      int ni = ci + dx[k], nj = cj + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == '#') continue;

      if (nj == cj + 1) {
        if (cdist[ni][nj] > cdist[ci][cj]) {
          cdist[ni][nj] = cdist[ci][cj];
          dq.push_front({ni, nj});
        }
      }
      else {
        if (cdist[ni][nj] > cdist[ci][cj] + 1) {
          cdist[ni][nj] = cdist[ci][cj] + 1;
          dq.push_back({ni, nj});
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
