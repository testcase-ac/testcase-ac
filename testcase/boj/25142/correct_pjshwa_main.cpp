#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAXN + 1][MAXN + 1];
int cdist[MAXN][MAXN][3];

int get_ns(int s, int k) {
  if (s == 0) return 1 + (k % 2 == 0);
  else if (s == 1) return k % 2 == 0 ? 1 : 0;
  else return k % 2 == 0 ? 0 : 2;
}

void solve() {
  int N, M, si, sj, fi, fj; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == 'S') si = i, sj = j;
      if (board[i][j] == 'F') fi = i, fj = j;
    }
  }

  memset(cdist, 0x3f, sizeof(cdist));
  deque<tuple<int, int, int>> q;
  q.emplace_back(si, sj, 0); cdist[si][sj][0] = 0;

  while (!q.empty()) {
    auto [x, y, s] = q.front(); q.pop_front();
    if (x == fi && y == fj) {
      cout << cdist[x][y][s] << '\n';
      return;
    }

    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M || board[nx][ny] == '#') continue;

      int ns = get_ns(s, k);
      int nd = cdist[x][y][s] + (s != ns);
      if (cdist[nx][ny][ns] > nd) {
        cdist[nx][ny][ns] = nd;
        if (s == ns) q.emplace_front(nx, ny, ns);
        else q.emplace_back(nx, ny, ns);
      }
    }
  }

  assert(false);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
