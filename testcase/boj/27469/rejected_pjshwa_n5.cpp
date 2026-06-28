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
int d[MAX + 1][MAX + 1][MAX + 1][9];
int Re, Ce, N, M, K;

int r(int i, int j, int k, int p) {
  if (d[i][j][k][p] != -1) return d[i][j][k][p];
  if (k == K) {
    return d[i][j][k][p] = (i == Re && j == Ce);
  }

  int ret = 0;
  for (int u = 0; u < 8; u++) {
    if (p == u) continue;

    for (int l = 1;; l++) {
      int ni = i + dx[u] * l, nj = j + dy[u] * l;
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) break;
      if (board[ni][nj] == '#') break;
      ret = (ret + r(ni, nj, k + 1, u)) % MOD;
    }
  }
  return d[i][j][k][p] = ret;
}

void solve() {
  cin >> N >> M >> K;
  for (int i = 0; i < N; i++) cin >> board[i];
  
  int Rs, Cs; cin >> Rs >> Cs >> Re >> Ce; Rs--; Cs--; Re--; Ce--;
  memset(d, -1, sizeof(d));
  cout << r(Rs, Cs, 0, 8) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
