#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 200, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, 0, -1}; // R, D, L, U
const int dy[] = {0, 1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int cdist[MAX][MAX][4];

// blocked at time t
int B[MAX][MAX][4];

bool is_numeric_char(char c) {
  return '0' <= c && c <= '9';
}

void solve() {
  int N, M; cin >> N >> M;
  int Sx, Sy, Ex, Ey; cin >> Sx >> Sy >> Ex >> Ey; --Sx; --Sy; --Ex; --Ey;
  for (int i = 0; i < N; ++i) cin >> board[i];

  // right
  for (int i = 0; i < N; ++i) {
    for (int t = 0; t < 4; ++t) {

    bool f = false;
    for (int j = 0; j < M; ++j) {
      char c = board[i][j];
        if (f) {
          if (c == '#' || is_numeric_char(c)) f = false;
        }
        if (is_numeric_char(c) && (c - '0' + t) % 4 == 0) f = true;
        B[i][j][t] |= f;
      }
    }
  }

  // down
  for (int j = 0; j < M; ++j) {
    for (int t = 0; t < 4; ++t) {
      bool f = false;
      for (int i = 0; i < N; ++i) {
        char c = board[i][j];
        if (f) {
          if (c == '#' || is_numeric_char(c)) f = false;
        }
        if (is_numeric_char(c) && (c - '0' + t + 3) % 4 == 0) f = true;
        B[i][j][t] |= f;
      }
    }
  }

  // left
  for (int i = 0; i < N; ++i) {
    for (int t = 0; t < 4; ++t) {
      bool f = false;
      for (int j = M - 1; j >= 0; --j) {
        char c = board[i][j];
        if (f) {
          if (c == '#' || is_numeric_char(c)) f = false;
        }
        if (is_numeric_char(c) && (c - '0' + t + 2) % 4 == 0) f = true;
        B[i][j][t] |= f;
      }
    }
  }

  // up
  for (int j = 0; j < M; ++j) {
    for (int t = 0; t < 4; ++t) {
      bool f = false;
      for (int i = N - 1; i >= 0; --i) {
        char c = board[i][j];
        if (f) {
          if (c == '#' || is_numeric_char(c)) f = false;
        }
        if (is_numeric_char(c) && (c - '0' + t + 1) % 4 == 0) f = true;
        B[i][j][t] |= f;
      }
    }
  }

  // for (int t = 0; t < 4; ++t) {
  //   cout << "t = " << t << '\n';
  //   for (int i = 0; i < N; ++i) {
  //     for (int j = 0; j < M; ++j)
  //       cout << B[i][j][t];
  //     cout << '\n';
  //   }
  // }

  queue<tuple<int, int, int>> q; memset(cdist, 0x3f, sizeof(cdist));
  q.emplace(Sx, Sy, 0); cdist[Sx][Sy][0] = 0;

  while (!q.empty()) {
    auto [x, y, t] = q.front(); q.pop();

    // move or stay
    for (int k = 0; k < 5; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

      int nt = (t + 1) % 4;
      if (B[nx][ny][nt] || board[nx][ny] != '.') continue;
      if (cdist[nx][ny][nt] > cdist[x][y][t] + 1) {
        cdist[nx][ny][nt] = cdist[x][y][t] + 1;
        q.emplace(nx, ny, nt);
      }
    }
  }
  
  int ans = INF;
  for (int t = 0; t < 4; ++t) ans = min(ans, cdist[Ex][Ey][t]);
  if (ans == INF) cout << "GG\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
