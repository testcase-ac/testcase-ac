#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
char board[MAX + 1][MAX + 1];
int d[MAX][MAX][4];
int N, M;

void solve_small() {
  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M - 2; j++) {
    if (board[i][j] == 'R' && board[i][j + 1] == 'G' && board[i][j + 2] == 'W') ans++;
  }
  cout << ans << '\n';
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];
  if (N <= 2) return solve_small();

  int ans = 0;
  for (int i = 0; i < N + M; i++) {
    int cur = 0;

    // 0: none / horiz, 1: 1 left, 2: 2 left, 3: 3 left
    for (int j = 0; j < M; j++) {
      int x = i - j, y = j;
      if (x < 0 || x >= N) continue;

      bool ha = y >= 2 && board[x][y - 2] == 'R' && board[x][y - 1] == 'G' && board[x][y] == 'W';
      bool va = x >= 2 && board[x - 2][y] == 'R' && board[x - 1][y] == 'G' && board[x][y] == 'W';

      int px = x + 1, py = y - 1;
      bool oob = px < 0 || px >= N || py < 0 || py >= M;

      if (oob) d[x][y][0] = ha;
      else {
        d[x][y][0] = max(d[x][y][0], d[px][py][0] + ha);
        d[x][y][0] = max(d[x][y][0], d[px][py][1] + ha);
        d[x][y][1] = d[px][py][2];
        d[x][y][2] = d[px][py][3];
      }

      if (va) {
        if (oob) d[x][y][3] = 1;
        else for (int w = 0; w < 4; w++) d[x][y][3] = max(d[x][y][3], d[px][py][w] + 1);
      }

      for (int w = 0; w < 4; w++) cur = max(cur, d[x][y][w]);
    }

    ans += cur;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
