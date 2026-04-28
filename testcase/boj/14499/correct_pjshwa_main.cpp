#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
const int dq[4][6] = {
	{1, 5, 2, 3, 0, 4},
  {4, 0, 2, 3, 5, 1},
  {3, 1, 0, 5, 4, 2},
  {2, 1, 5, 0, 4, 3}
};
int board[MAX][MAX];

void solve() {
  int N, M, x, y, Q;
  cin >> N >> M >> x >> y >> Q;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> board[i][j];

  int t = 0;
  int p[6] = {0}, n[6] = {0};
  while (Q--) {
    int o, k;
    cin >> o;

    if (o == 1) k = 3;
    if (o == 2) k = 2;
    if (o == 3) k = 0;
    if (o == 4) k = 1;

    int nx = x + dx[k], ny = y + dy[k];
    if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

    for (int l = 0; l < 6; l++) n[l] = p[dq[k][l]];
    for (int l = 0; l < 6; l++) p[l] = n[l];
    x = nx, y = ny;

    if (board[x][y]) p[5] = board[x][y], board[x][y] = 0;
    else board[x][y] = p[5];

    cout << p[0] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
