#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4000, BIAS = 2000, INF = 0x3f3f3f3f;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1];
int nboard[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];
int from[MAX + 1][MAX + 1];
int lb, rb, ub, db;

bool oob(int x, int y) {
  return x < ub || x > db || y < lb || y > rb;
}

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  int minx = INF, maxx = -1, miny = INF, maxy = -1, si, sj;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == 'H') si = i, sj = j;
    if (board[i][j] == 'T') {
      minx = min(minx, i);
      maxx = max(maxx, i);
      miny = min(miny, j);
      maxy = max(maxy, j);
    }
  }

  vector<pii> obs_rel;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '#') obs_rel.push_back({i - si, j - sj});
    if (board[i][j] == 'T') nboard[i - si + BIAS][j - sj + BIAS] = 1;
  }
  lb = maxy + 1 - M, rb = miny, ub = maxx + 1 - N, db = minx;

  queue<pii> q;
  q.push({0, 0});
  vis[BIAS][BIAS] = true;

  memset(from, -1, sizeof(from));

  int ex = -INF, ey = -INF;
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    if (nboard[x + BIAS][y + BIAS] == 1) {
      ex = x, ey = y;
      break;
    }

    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (oob(nx, ny) || vis[nx + BIAS][ny + BIAS]) continue;

      bool able = true;
      for (auto& [dx, dy] : obs_rel) {
        if (nboard[nx + dx + BIAS][ny + dy + BIAS] == 1) {
          able = false;
          break;
        }
      }
      if (!able) continue;

      vis[nx + BIAS][ny + BIAS] = true;
      from[nx + BIAS][ny + BIAS] = k;
      q.push({nx, ny});
    }
  }

  if (ex == -INF) return cout << "-1\n", void();

  stack<char> traj;
  while (from[ex + BIAS][ey + BIAS] != -1) {
    int k = from[ex + BIAS][ey + BIAS];
    ex = ex - dx[k], ey = ey - dy[k];

    if (k == 0) traj.push('U');
    if (k == 1) traj.push('L');
    if (k == 2) traj.push('D');
    if (k == 3) traj.push('R');
  }

  while (!traj.empty()) {
    cout << traj.top();
    traj.pop();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
