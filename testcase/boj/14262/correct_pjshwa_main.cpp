#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 55][MAX + 55];
int dt[3][MAX + 1];

int main() {
  fast_io();

  int n, m;
  ll t;
  cin >> n >> m >> t;
  for (int i = 0; i < n; i++) cin >> board[i];

  int rc = 0, rt = 0, gc = 0, gt = 0, bc = 0, bt = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == '.') continue;

    if (board[i][j] == 'R') rc++;
    if (board[i][j] == 'G') gc++;
    if (board[i][j] == 'B') bc++;

    for (int k = 1; k <= MAX; k++) {
      if (board[i + k][j + k] == 'R') {
        dt[0][k]++;
        break;
      }
      if (board[i + k][j + k] == 'G') {
        dt[1][k]++;
        break;
      }
      if (board[i + k][j + k] == 'B') {
        dt[2][k]++;
        break;
      }
    }
  }

  ll ra = t * rc, ga = t * gc, ba = t * bc;
  for (int k = 1; k <= min(t, (ll)MAX); k++) {
    ra -= dt[0][k] * (t - k);
    ga -= dt[1][k] * (t - k);
    ba -= dt[2][k] * (t - k);
  }
  cout << ra << '\n' << ga << '\n' << ba << '\n';
}
