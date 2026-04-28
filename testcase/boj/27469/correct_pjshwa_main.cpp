#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MOD = 998244353;
const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
char board[MAX + 1][MAX + 1];

// prefix sum dir, x, y, last dir
int P[8][MAX][MAX][8], U[MAX][MAX][8];
int N, M, K;

void solve() {
  cin >> N >> M >> K;
  for (int i = 0; i < N; i++) cin >> board[i];
  int Rs, Cs, Re, Ce; cin >> Rs >> Cs >> Re >> Ce; Rs--; Cs--; Re--; Ce--;

  for (int d = 0; d < 8; d++) {
    for (int l = 1;; l++) {
      int ni = Rs + dx[d] * l, nj = Cs + dy[d] * l;
      if (ni < 0 || ni >= N || nj < 0 || nj >= M || board[ni][nj] == '#') break;
      U[ni][nj][d] = 1;
    }
  }

  for (int d = 0; d < 8; d++) {
    int di = dx[d] == -1 ? -1 : 1, dj = dy[d] == -1 ? -1 : 1;
    int si = di == -1 ? N - 1 : 0, sj = dj == -1 ? M - 1 : 0;
    int ei = di == -1 ? 0 : N - 1, ej = dj == -1 ? 0 : M - 1;

    for (int i = si; i != ei + di; i += di) for (int j = sj; j != ej + dj; j += dj) for (int u = 0; u < 8; u++) {
      if (board[i][j] == '#') continue;
      int pi = i - dx[d], pj = j - dy[d];
      if (pi < 0 || pi >= N || pj < 0 || pj >= M) P[d][i][j][u] = U[i][j][u];
      else P[d][i][j][u] = (P[d][pi][pj][u] + U[i][j][u]) % MOD;
    }
  }

  for (int t = 1; t < K; t++) {
    memset(U, 0, sizeof(U));
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) for (int u = 0; u < 8; u++) {
      if (board[i][j] == '#') continue;

      for (int d = 0; d < 8; d++) {
        if (u == d) continue;
        int pi = i - dx[u], pj = j - dy[u];
        if (pi < 0 || pi >= N || pj < 0 || pj >= M) continue;
        U[i][j][u] = (U[i][j][u] + P[u][pi][pj][d]) % MOD;
      }
    }

    memset(P, 0, sizeof(P));
    for (int d = 0; d < 8; d++) {
      int di = dx[d] == -1 ? -1 : 1, dj = dy[d] == -1 ? -1 : 1;
      int si = di == -1 ? N - 1 : 0, sj = dj == -1 ? M - 1 : 0;
      int ei = di == -1 ? 0 : N - 1, ej = dj == -1 ? 0 : M - 1;

      for (int i = si; i != ei + di; i += di) for (int j = sj; j != ej + dj; j += dj) for (int u = 0; u < 8; u++) {
        if (board[i][j] == '#') continue;
        int pi = i - dx[d], pj = j - dy[d];
        if (pi < 0 || pi >= N || pj < 0 || pj >= M) P[d][i][j][u] = U[i][j][u];
        else P[d][i][j][u] = (P[d][pi][pj][u] + U[i][j][u]) % MOD;
      }
    }
  }

  int ans = 0;
  for (int u = 0; u < 8; u++) ans = (ans + U[Re][Ce][u]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
