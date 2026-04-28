#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;
int R[MAX + 1][MAX + 1], S[MAX + 1][MAX + 1];
int d[MAX + 1][MAX + 1][MAX + 1][MAX + 1];
int n, m;

int r(int x1, int y1, int x2, int y2) {
  if (d[x1][y1][x2][y2] != -1) return d[x1][y1][x2][y2];
  if (x1 == x2 && y1 == y2) return d[x1][y1][x2][y2] = 0;

  int val = INF;
  for (int nx = x1; nx < x2; nx++) {
    val = min(val, r(x1, y1, nx, y2) + r(nx + 1, y1, x2, y2));
  }
  for (int ny = y1; ny < y2; ny++) {
    val = min(val, r(x1, y1, x2, ny) + r(x1, ny + 1, x2, y2));
  }
  val += S[x2][y2] - S[x1 - 1][y2] - S[x2][y1 - 1] + S[x1 - 1][y1 - 1];

  return d[x1][y1][x2][y2] = val;
}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> R[i][j];

  for (int j = 1; j <= m; j++) S[1][j] = R[1][j] + S[1][j - 1];
  for (int i = 1; i <= n; i++) S[i][1] = R[i][1] + S[i - 1][1];
  for (int i = 2; i <= n; i++) for (int j = 2; j <= m; j++) {
    S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + R[i][j];
  }

  memset(d, -1, sizeof(d));
  cout << r(1, 1, n, m) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
