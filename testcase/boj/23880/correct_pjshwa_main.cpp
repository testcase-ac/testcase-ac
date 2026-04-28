#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];

// rotation, direction, i, j
int d[5][2][MAX][MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> board[i];

  memset(d, 0, sizeof(d));
  for (int i = 0; i < n; i++) {
    if (board[i][0] == 'H') break;
    d[0][1][i][0] = 1;
  }
  for (int j = 0; j < n; j++) {
    if (board[0][j] == 'H') break;
    d[0][0][0][j] = 1;
  }
  for (int i = 1; i < n; i++) for (int j = 1; j < n; j++) {
    if (board[i][j] == 'H') continue;

    for (int l = 0; l <= 3; l++) {
      d[l][0][i][j] += d[l][0][i][j - 1];
      d[l + 1][0][i][j] += d[l][1][i][j - 1];
      d[l][1][i][j] += d[l][1][i - 1][j];
      d[l + 1][1][i][j] += d[l][0][i - 1][j];
    }
  }

  ll ans = 0;
  for (int l = 0; l <= k; l++) ans += (d[l][0][n - 1][n - 1] + d[l][1][n - 1][n - 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
