#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50, INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
int U[MAX + 1][MAX + 1], ON[MAX + 1][MAX + 1], OF[MAX + 1][MAX + 1];
int P[MAX + 1][MAX + 1], ans = 0;
int R, C;
int cdist[MAX + 1][MAX + 1];
pii from[MAX + 1][MAX + 1];

void do_work(int sx, int sy, int ex, int ey, int st) {
  for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
    cdist[i][j] = INF;
    from[i][j] = {-1, -1};
  }

  queue<tii> q;
  q.push({sx, sy, st});
  cdist[sx][sy] = st;

  while (!q.empty()) {
    auto [x, y, t] = q.front();
    q.pop();

    if (x == ex && y == ey) break;

    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
      if (board[nx][ny] == '#') continue;
      if (cdist[nx][ny] <= t + 1) continue;
      cdist[nx][ny] = t + 1;
      from[nx][ny] = {x, y};
      q.push({nx, ny, t + 1});
    }
  }

  while (ex != sx || ey != sy) {
    auto [px, py] = from[ex][ey];

    if (P[px][py] == -1) ans += ON[px][py];
    else {
      int gap = cdist[px][py] - P[px][py];
      ans += min(gap * U[px][py], OF[px][py] + ON[px][py]);
    }
    P[px][py] = cdist[px][py];
    ex = px, ey = py;
  }
}

void solve() {
  int M;
  cin >> R >> C >> M;
  for (int i = 0; i < R; i++) cin >> board[i];
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) cin >> U[i][j];
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) cin >> ON[i][j];
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) cin >> OF[i][j];

  memset(P, -1, sizeof(P));
  int sx, sy, t = 0;
  cin >> sx >> sy;
  while (--M) {
    int px, py;
    cin >> px >> py;

    do_work(sx, sy, px, py, t);
    t = cdist[px][py];

    sx = px, sy = py;
  }

  if (P[sx][sy] == -1) ans += ON[sx][sy];
  else {
    int gap = cdist[sx][sy] - P[sx][sy];
    ans += min(gap * U[sx][sy], OF[sx][sy] + ON[sx][sy]);
  }
  P[sx][sy] = t;

  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    if (P[i][j] != -1) ans += OF[i][j];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
