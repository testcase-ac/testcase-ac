#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
int board[MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> board[i][j];

  int ans = -1;
  while (1) {
    ans++;

    int r = 0;
    for (int i = 1; i <= n; i++) for (int j = m; j >= r; j--) {
      if (board[i][j] == 0) continue;

      int nr = j;
      for (int k = j; k >= r; k--) {
        if (board[i][k] == 1) board[i][k] = 0;
      }

      r = nr;
      break;
    }

    if (r == 0) break;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
