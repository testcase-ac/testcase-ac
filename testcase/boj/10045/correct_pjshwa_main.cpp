#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 0, -1, -1}, dy[4] = {-1, 0, -1, 0};
char board[MAX + 10][MAX + 10], emb[2][3];
int w[MAX][MAX];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];
  for (int i = 0; i < 2; i++) cin >> emb[i];

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    int p[4] = {0};
    if (board[i][j] == emb[0][0]) p[0] = 1;
    if (board[i][j + 1] == emb[0][1]) p[1] = 1;
    if (board[i + 1][j] == emb[1][0]) p[2] = 1;
    if (board[i + 1][j + 1] == emb[1][1]) p[3] = 1;

    for (int k = 0; k < 4; k++) {
      w[i][j] *= 2;
      w[i][j] += p[k];
    }
  }

  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (w[i][j] == 15) ans++;
  }

  int oans = ans;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    int cur = oans;
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      if (w[ni][nj] == 15) cur--;
    }

    char o = board[i][j];
    for (char c : string("JOI")) {
      int ccur = cur;
      board[i][j] = c;

      for (int k = 0; k < 4; k++) {
        int ni = i + dx[k], nj = j + dy[k];
        if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

        int p[4] = {0}, a = 0;
        if (board[ni][nj] == emb[0][0]) p[0] = 1;
        if (board[ni][nj + 1] == emb[0][1]) p[1] = 1;
        if (board[ni + 1][nj] == emb[1][0]) p[2] = 1;
        if (board[ni + 1][nj + 1] == emb[1][1]) p[3] = 1;

        for (int l = 0; l < 4; l++) {
          a *= 2;
          a += p[l];
        }

        if (a == 15) ccur++;
      }

      ans = max(ans, ccur);
    }

    board[i][j] = o;
  }

  cout << ans << '\n';


}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
