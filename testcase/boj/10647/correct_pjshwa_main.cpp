#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
char board[MAX + 1][MAX + 1];
int LS[MAX][MAX], RS[MAX][MAX];
int N, M;

void update(int i) {
  for (int j = 0; j < M; j++) {
    LS[i][j] = j == 0 ? -1 : LS[i][j - 1];
    if (board[i][j] == 'x') LS[i][j] = j;
  }
  for (int j = M - 1; j >= 0; j--) {
    RS[i][j] = j == M - 1 ? -1 : RS[i][j + 1];
    if (board[i][j] == 'x') RS[i][j] = j;
  }
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    update(i);
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int x, y;
    cin >> x >> y;
    x--, y--;

    int ans = INF;
    for (int i = 0; i < N; i++) {
      int xdist = (x - i) * (x - i);

      if (LS[i][y] != -1) ans = min(ans, xdist + (y - LS[i][y]) * (y - LS[i][y]));
      if (RS[i][y] != -1) ans = min(ans, xdist + (y - RS[i][y]) * (y - RS[i][y]));
    }
    cout << ans << '\n';

    board[x][y] = 'x';
    update(x);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
