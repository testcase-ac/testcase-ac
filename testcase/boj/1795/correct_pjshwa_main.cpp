#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10;
const int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
char board[MAXN + 1][MAXN + 1];
int cdist[MAXN * MAXN][MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;
  vector<pii> objs;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] != '.') objs.emplace_back(i, j);
    }
  }
  memset(cdist, -1, sizeof(cdist));

  int Z = objs.size();
  queue<pii> q;
  for (int t = 0; t < Z; ++t) {
    auto [i, j] = objs[t];
    int k = board[i][j] - '0';
    q.push({i, j}); cdist[t][i][j] = 0;

    while (!q.empty()) {
      auto [x, y] = q.front(); q.pop();
      for (int d = 0; d < 8; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M || cdist[t][nx][ny] != -1) continue;
        cdist[t][nx][ny] = cdist[t][x][y] + 1;
        q.push({nx, ny});
      }
    }

    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
      if (cdist[t][i][j] == -1) continue;
      cdist[t][i][j] = (cdist[t][i][j] + k - 1) / k;
    }
  }

  int ans = INT_MAX;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int sum = 0, ok = 1;
    for (int t = 0; t < Z; ++t) {
      if (cdist[t][i][j] == -1) {
        ok = 0; break;
      }
      sum += cdist[t][i][j];
    }
    if (ok) ans = min(ans, sum);
  }
  if (ans == INT_MAX) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
