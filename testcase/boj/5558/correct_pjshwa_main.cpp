#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int cx[10], cy[10];
char board[MAX + 1][MAX + 1];
int cdist[MAX][MAX];
int N, M, C;

int bfs(int si, int sj, int ei, int ej) {
  memset(cdist, -1, sizeof(cdist));

  queue<pii> q;
  q.push({si, sj});
  cdist[si][sj] = 0;

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();

    if (i == ei && j == ej) return cdist[i][j];

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == 'X') continue;
      if (cdist[ni][nj] != -1) continue;

      cdist[ni][nj] = cdist[i][j] + 1;
      q.push({ni, nj});
    }
  }

  return -1;
}

void solve() {
  cin >> N >> M >> C;
  for (int i = 0; i < N; i++) cin >> board[i];

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == 'S') cx[0] = i, cy[0] = j;
    else if ('1' <= board[i][j] && board[i][j] <= '9') {
      int c = board[i][j] - '0';
      cx[c] = i, cy[c] = j;
    }
  }

  int ans = 0;
  for (int i = 0; i < C; i++) ans += bfs(cx[i], cy[i], cx[i + 1], cy[i + 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
