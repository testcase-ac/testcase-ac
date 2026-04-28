#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
int board[MAX + 1][MAX + 1], pf[MAX + 1][MAX + 1];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> board[i][j];

  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    pf[i][j] = board[i][j];
    pf[i][j] += pf[i - 1][j];
    pf[i][j] += pf[i][j - 1];
    pf[i][j] -= pf[i - 1][j - 1];
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    for (int x = 0; x < 10; x++) for (int y = 0; y < 10; y++) {
      int a = i - x, b = j - y;
      if (a < 1 || b < 1) continue;

      int c = pf[i][j] - pf[a - 1][j] - pf[i][b - 1] + pf[a - 1][b - 1];
      if (c == 10) ans++;
    }
  }

  cout << ans << '\n';
}
