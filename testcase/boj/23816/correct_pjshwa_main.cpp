#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
int d[5001][10001];

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) d[i][j] = -INF;
  d[0][0] = 0;

  for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) {
    d[i][j] = max(d[i][j], d[i - 1][j]);
    if (j >= 1) {
      int res = d[i - 1][j - 1];
      if (res != -INF) d[i][j] = max(d[i][j], res + 1);
    }
    if (j >= 3) {
      int res = d[i - 1][j - 3];
      if (res != -INF) d[i][j] = max(d[i][j], res + 2);
    }
    if (j >= 7) {
      int res = d[i - 1][j - 7];
      if (res != -INF) d[i][j] = max(d[i][j], res + 4);
    }
    if (j >= 15) {
      int res = d[i - 1][j - 15];
      if (res != -INF) d[i][j] = max(d[i][j], res);
    }
  }

  int ans = d[n][m];
  if (ans == -INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
