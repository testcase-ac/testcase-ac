#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_lower(char c) {
  return 'a' <= c && c <= 'z';
}

bool is_set_lower(char c, int state) {
  int pos = c - (is_lower(c) ? 'a' : 'A');
  for (int j = 0; j < pos; ++j) state /= 3;
  return state % 3 == 1;
}

bool is_set_upper(char c, int state) {
  int pos = c - (is_lower(c) ? 'a' : 'A');
  for (int j = 0; j < pos; ++j) state /= 3;
  return state % 3 == 2;
}

bool is_set(char c, int state) {
  return is_lower(c) ? is_set_lower(c, state) : is_set_upper(c, state);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

// 3^10 = 59049
const int MAXS = 59049;
char board[MAXN + 1][MAXN + 1];
int cdist[MAXN][MAXN];

void solve() {
  int N, ans = INF; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  queue<pii> q;
  for (int s = 1; s < MAXS; ++s) {
    int ok = is_set(board[0][0], s);
    for (char c = 'a'; c <= 'z'; ++c) {
      if (is_set_lower(c, s) && is_set_upper(c, s)) ok = 0;
    }
    if (!ok) continue;

    memset(cdist, 0x3f, sizeof(cdist));
    q.push({0, 0}); cdist[0][0] = 1;

    while (!q.empty()) {
      auto [x, y] = q.front(); q.pop();
      int dist = cdist[x][y];
      if (x == N - 1 && y == N - 1) ans = min(ans, dist);

      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (!is_set(board[nx][ny], s)) continue;
        if (cdist[nx][ny] == INF) {
          cdist[nx][ny] = dist + 1;
          q.push({nx, ny});
        }
      }
    }
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
