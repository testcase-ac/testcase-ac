#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

int d[10001][101];
int r(int n, int m) {
  if (n == 0 || m == 0) return 0;
  if (d[n][m] != -1) return d[n][m];
  if (n == 1) return d[n][m] = m;
  if (m == 1) return d[n][m] = n;
  if (n == m) return d[n][m] = 1;

  // Hack...
  if (n >= 3 * m) return d[n][m] = r(n - m, m) + 1;

  int ans = INF;
  for (int d = 1; d <= (n + 1) / 2; d++) ans = min(ans, r(n - d, m) + r(d, m));
  for (int d = 1; d <= (m + 1) / 2; d++) ans = min(ans, r(n, m - d) + r(n, d));
  return d[n][m] = ans;
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  memset(d, -1, sizeof(d));
  cout << r(n, m) << '\n';
}
