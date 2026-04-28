#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
char board[MAXN + 1][MAXN + 1];
int cdist[MAXN][MAXN];

void solve() {
  int N, M, si = -1, sj, ei, ej; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == 'A') {
        if (si == -1) si = i, sj = j;
        else ei = i, ej = j;
      }
    }
  }

  auto oob = [&](int i, int j) {
    return i < 0 || i >= N || j < 0 || j >= M;
  };

  deque<pii> dq; int ans = INF;
  for (int k = 0; k < 4; ++k) {
    int qi = si + dx[k], qj = sj + dy[k];
    if (oob(qi, qj) || board[qi][qj] == '#') continue;

    memset(cdist, 0x3f, sizeof(cdist));
    dq.emplace_back(qi, qj); cdist[qi][qj] = (board[qi][qj] == 'O' ? 1 : 0);

    while (!dq.empty()) {
      auto [i, j] = dq.front(); dq.pop_front();
      if (i == ei && j == ej) continue;

      for (int d = 0; d < 4; ++d) {
        int ni = i + dx[d], nj = j + dy[d];
        if (oob(ni, nj) || board[ni][nj] == '#') continue;
        if (ni == si && nj == sj) continue;

        if (board[ni][nj] == 'O') {
          if (cdist[ni][nj] > cdist[i][j] + 1) {
            cdist[ni][nj] = cdist[i][j] + 1;
            dq.emplace_back(ni, nj);
          }
        } else {
          if (cdist[ni][nj] > cdist[i][j]) {
            cdist[ni][nj] = cdist[i][j];
            dq.emplace_front(ni, nj);
          }
        }
      }
    }

    int cnt = 0, cur = cdist[ei][ej];
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
      cnt += (board[i][j] == 'O' && cdist[i][j] != INF);
    }
    if (cur == INF) continue;
    if (cur % 2 == 1) {
      if (cur < cnt) ++cur;
      else continue;
    }

    assert(cur % 2 == 0);
    ans = min(ans, 1 + cur / 2);
  }

  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
