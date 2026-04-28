#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];
int P[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    cin >> (board[i] + 1);
    for (int j = 1; j <= M; ++j) {
      P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + (board[i][j] == 'x');
    }
  }

  int si = -1, sj;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
    if (board[i][j] == 'x' && si == -1) si = i, sj = j;
  }
  int p = 1;
  while (si + p <= N && sj + p <= M) {
    int cnt = P[si + p][sj + p] - P[si - 1][sj + p] - P[si + p][sj - 1] + P[si - 1][sj - 1];
    if (cnt == (p + 1) * (p + 1)) ++p;
    else break;
  }
  cout << si << ' ' << sj << ' ' << p << '\n';

  int total = P[N][M];
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
    if (board[i][j] != 'x') continue;

    int q = 1;
    while (1) {
      // Calculate overlapping region of two squares:
      // (i, j) ~ (i + q, j + q) and (si, sj) ~ (si + p, sj + p)
      int x = max(i, si), y = max(j, sj);
      int h = min(i + q, si + p) - x, w = min(j + q, sj + p) - y;
      h = max(0, h), w = max(0, w);

      if (total == p * p + q * q - h * w) {
        cout << i << ' ' << j << ' ' << q << '\n';
        return;
      }

      if (i + q > N || j + q > M) break;
      int cnt = P[i + q][j + q] - P[i - 1][j + q] - P[i + q][j - 1] + P[i - 1][j - 1];
      if (cnt == (q + 1) * (q + 1)) ++q;
      else break;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
