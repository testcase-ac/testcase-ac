#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
char board[MAXN + 1][MAXN + 1];
int cdist[MAXN][MAXN], N, M;

// calculate distance from starting point
void f_cdist(int i, int j) {
  memset(cdist, 0x3f, sizeof(cdist));

  queue<pii> q;
  q.emplace(i, j); cdist[i][j] = 0;
  while (!q.empty()) {
    auto [ci, cj] = q.front(); q.pop();
    for (int k = 0; k < 4; ++k) {
      int ni = ci + dx[k], nj = cj + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == '#' || cdist[ni][nj] != INF) continue;
      cdist[ni][nj] = cdist[ci][cj] + 1;
      q.emplace(ni, nj);
    }
  }
}

void solve() {
  cin >> M >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  int si, sj;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '#') continue;
    si = i, sj = j;
    break;
  }

  f_cdist(si, sj);
  int max_dist = -1, mi, mj;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '#') continue;
    if (max_dist < cdist[i][j]) max_dist = cdist[i][j], mi = i, mj = j;
  }

  f_cdist(mi, mj);
  max_dist = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '#') continue;
    max_dist = max(max_dist, cdist[i][j]);
  }

  cout << "Maximum rope length is " << max_dist << ".\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
