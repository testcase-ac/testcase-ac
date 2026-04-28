#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 11, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
char board[MAXN + 1][MAXN + 1];
int Vcnt[MAXN][MAXN], Tvis[MAXN][MAXN], Dr[MAXN][MAXN], Dc[MAXN][MAXN];

void solve() {
  int N; cin >> N;

  int si, sj, Tcnt = 0;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < N; ++j) {
      if (board[i][j] == 'S') si = i, sj = j;
      if (board[i][j] == '.') ++Tcnt;
    }
  }
  if (Tcnt == 0) return cout << "0\n", void();

  queue<tuple<int, int, int, int, int>> Q;
  Tvis[si][sj] = 1;
  for (int k = 0; k < 4; ++k) {
    int ni = si + dx[k], nj = sj + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= N || board[ni][nj] == '@') continue;
    Q.emplace(ni, nj, dx[k], dy[k], 0);
  }

  for (int it = 1; it <= 100000; ++it) {
    memset(Dr, 0, sizeof(Dr));
    memset(Dc, 0, sizeof(Dc));
    memset(Vcnt, 0, sizeof(Vcnt));

    while (!Q.empty()) {
      auto [ci, cj, di, dj, type] = Q.front(); Q.pop();
      if (Tvis[ci][cj] == 0) Tvis[ci][cj] = 1, --Tcnt;
      if (di == 0 && dj == 0) continue;

      if (type == 0) {
        for (int k = 0; k < 4; ++k) {
          int ni = ci + dx[k], nj = cj + dy[k];
          int pi = ci - di, pj = cj - dj;
          if (ni < 0 || ni >= N || nj < 0 || nj >= N || board[ni][nj] == '@') continue;
          if (ni == pi && nj == pj) continue;
          Dr[ni][nj] += ni - ci; Dc[ni][nj] += nj - cj;
          Vcnt[ni][nj] += 1;
        }
      }
      else {
        int ni = ci + di, nj = cj + dj;
        if (ni < 0 || ni >= N || nj < 0 || nj >= N || board[ni][nj] == '@') continue;
        Dr[ni][nj] += di; Dc[ni][nj] += dj;
        Vcnt[ni][nj] += 2;
      }
    }

    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
      if (Vcnt[i][j] == 0) continue;
      int type = Vcnt[i][j] != 1;
      Q.emplace(i, j, Dr[i][j], Dc[i][j], type);
    }

    if (Tcnt == 0) return cout << it << '\n', void();
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
