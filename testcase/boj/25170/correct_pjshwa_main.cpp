#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, MAXT = 500, INF = 1e9 + 7;
int w[MAX][MAX], t[MAX][MAX];
int d[MAX][MAX][MAXT + 1];
int n, m, T;

int r(int i, int j, int ct) {
  if (ct > T) return -INF;
  if (d[i][j][ct] != -1) return d[i][j][ct];
  if (i == n - 1 && j == m - 1) return d[i][j][ct] = 0;

  int res = -INF;
  if (i < n - 1) {
    res = max(res, r(i + 1, j, ct + 1));
    if (ct + t[i][j] + 1 <= T) res = max(res, r(i + 1, j, ct + t[i][j] + 1) + w[i][j]);
  }
  if (j < m - 1) {
    res = max(res, r(i, j + 1, ct + 1));
    if (ct + t[i][j] + 1 <= T) res = max(res, r(i, j + 1, ct + t[i][j] + 1) + w[i][j]);
  }
  if (i < n - 1 && j < m - 1) {
    res = max(res, r(i + 1, j + 1, ct + 1));
    if (ct + t[i][j] + 1 <= T) res = max(res, r(i + 1, j + 1, ct + t[i][j] + 1) + w[i][j]);
  }

  return d[i][j][ct] = res;
}

void solve() {
  cin >> n >> m >> T;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> w[i][j];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> t[i][j];

  memset(d, -1, sizeof d);
  cout << r(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
