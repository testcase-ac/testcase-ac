#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};
int board[MAX + 10][MAX + 10], terminal[MAX + 10][MAX + 10];

int cdir(int odir) {
  if (odir == 0) return 1;
  if (odir == 1) return 0;
  if (odir == 2) return 3;
  if (odir == 3) return 2;
}

void traverse(int cx, int cy, int dir) {

  while (1) {
    int nx = cx + dx[dir], ny = cy + dy[dir];
    if (board[nx][ny]) dir = cdir(dir);
    cx = nx, cy = ny;

    if (terminal[cx][cy]) {
      cout << terminal[cx][cy] << ' ';
      break;
    }
  }

}

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> board[i][j];

  for (int i = 1; i <= N; i++) terminal[i][0] = i;
  for (int j = 1; j <= M; j++) terminal[N + 1][j] = N + j;
  for (int i = N; i >= 1; i--) terminal[i][M + 1] = N + M + (N + 1 - i);
  for (int j = M; j >= 1; j--) terminal[0][j] = 2 * N + M + (M + 1 - j);

  for (int i = 1; i <= N; i++) traverse(i, 0, 0);
  for (int j = 1; j <= M; j++) traverse(N + 1, j, 1);
  for (int i = N; i >= 1; i--) traverse(i, M + 1, 2);
  for (int j = M; j >= 1; j--) traverse(0, j, 3);

  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
