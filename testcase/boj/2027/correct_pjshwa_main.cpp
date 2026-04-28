#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 150;
char board[MAX + 5][MAX + 5];
int P[MAX + 5][MAX + 5];
int U[MAX + 5][MAX + 5][MAX + 5], D[MAX + 5][MAX + 5][MAX + 5];

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> (board[i] + 1);
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + (board[i][j] == '1');
  }

  for (int j1 = 1; j1 <= m; ++j1) for (int j2 = j1; j2 <= m; ++j2) {
    for (int i = 1; i <= n; ++i) {
      int cnt = j2 - j1 + 1, real = P[i][j2] - P[i][j1 - 1] - P[i - 1][j2] + P[i - 1][j1 - 1];
      bool filled = real == cnt;
      if (filled) U[i][j1][j2] = U[i - 1][j1][j2] + cnt;
      else U[i][j1][j2] = 0;
    }
    for (int i = n; i >= 1; --i) {
      int cnt = j2 - j1 + 1, real = P[i][j2] - P[i][j1 - 1] - P[i - 1][j2] + P[i - 1][j1 - 1];
      bool filled = real == cnt;
      if (filled) D[i][j1][j2] = D[i + 1][j1][j2] + cnt;
      else D[i][j1][j2] = 0;
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j1 = 1; j1 <= m; ++j1) {
      int umax = U[i - 1][j1][j1];
      for (int j2 = j1 + 1; j2 <= m; ++j2) {
        int dmax = D[i][j1][j2];
        if (umax > 0 && dmax > 0) ans = max(ans, umax + dmax);
        umax = max(umax, U[i - 1][j1][j2]);
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
