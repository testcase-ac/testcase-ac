#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0 ,0};
char board[MAX + 1][MAX + 1];
int pdist[MAX][MAX], cdist[MAX][MAX];

void solve() {
  int N, M; cin >> N >> M;

  int si, sj, ei, ej;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 'V') si = i, sj = j;
      else if (board[i][j] == 'J') ei = i, ej = j;
    }
  }

  queue<pii> q;
  memset(pdist, 0x3f, sizeof(pdist));
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '+') q.push({i, j}), pdist[i][j] = 0;
  }

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
      int ni = i + dy[d], nj = j + dx[d];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (pdist[ni][nj] > pdist[i][j] + 1) {
        pdist[ni][nj] = pdist[i][j] + 1;
        q.push({ni, nj});
      }
    }
  }

  int left = 0, right = 100000;
  while (left < right) {
    int mid = (left + right) / 2;

    memset(cdist, 0x3f, sizeof(cdist));
    q.push({si, sj}); cdist[si][sj] = 0;

    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();
      for (int d = 0; d < 4; d++) {
        int ni = i + dy[d], nj = j + dx[d];
        if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
        if (pdist[ni][nj] <= mid || cdist[ni][nj] <= cdist[i][j] + 1) continue;
        cdist[ni][nj] = cdist[i][j] + 1;
        q.push({ni, nj});
      }
    }
    if (pdist[si][sj] > mid && cdist[ei][ej] < INF) left = mid + 1;
    else right = mid;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
