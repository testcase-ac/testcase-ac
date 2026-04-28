#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 15, INF = 1e9 + 7;
int oboard[MAX][MAX], board[MAX][MAX];

int dist(int ai, int aj, int bi, int bj) {
  return abs(ai - bi) + abs(aj - bj);
}

void solve() {
  int n, m, d;
  cin >> n >> m >> d;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> oboard[i][j];

  int ans = 0, cur;
  for (int a = 0; a < m; a++) for (int b = a + 1; b < m; b++) for (int c = b + 1; c < m; c++) {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) board[i][j] = oboard[i][j];
    cur = 0;

    bool changed = true;
    while (changed) {
      changed = false;

      int ai = INF, aj = INF, adist = INF;
      for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        int cadist = dist(n, a, i, j);
        if (cadist > d || !board[i][j]) continue;
        if (cadist < adist) adist = cadist, ai = i, aj = j;
        else if (cadist == adist && aj > j) ai = i, aj = j;
      }

      int bi = INF, bj = INF, bdist = INF;
      for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        int cbdist = dist(n, b, i, j);
        if (cbdist > d || !board[i][j]) continue;
        if (cbdist < bdist) bdist = cbdist, bi = i, bj = j;
        else if (cbdist == bdist && bj > j) bi = i, bj = j;
      }

      int ci = INF, cj = INF, cdist = INF;
      for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        int ccdist = dist(n, c, i, j);
        if (ccdist > d || !board[i][j]) continue;
        if (ccdist < cdist) cdist = ccdist, ci = i, cj = j;
        else if (ccdist == cdist && cj > j) ci = i, cj = j;
      }

      if (ai != INF && board[ai][aj]) board[ai][aj] = 0, cur++;
      if (bi != INF && board[bi][bj]) board[bi][bj] = 0, cur++;
      if (ci != INF && board[ci][cj]) board[ci][cj] = 0, cur++;

      for (int i = n - 1; i >= 0; i--) for (int j = 0; j < m; j++) {
        if (!board[i][j]) continue;

        changed = true;
        board[i][j] = 0;
        if (i != n - 1) board[i + 1][j] = 1;
      }
    }

    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
