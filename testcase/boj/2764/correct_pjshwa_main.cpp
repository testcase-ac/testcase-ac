#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[6];
uint d[31][31][31][31][31];

void solve() {
  int n;
  cin >> n;

  memset(a, 0, sizeof(a));
  memset(d, 0, sizeof(d));
  for (int i = 0; i < n; i++) cin >> a[i];

  d[0][0][0][0][0] = 1;
  for (int i = 0; i <= a[0]; i++) for (int j = 0; j <= a[1]; j++) for (int k = 0; k <= a[2]; k++) 
  for (int l = 0; l <= a[3]; l++) for (int m = 0; m <= a[4]; m++) {
    if (i < a[0]) d[i + 1][j][k][l][m] += d[i][j][k][l][m];
    if (j < min({a[1], i})) d[i][j + 1][k][l][m] += d[i][j][k][l][m];
    if (k < min({a[2], i, j})) d[i][j][k + 1][l][m] += d[i][j][k][l][m];
    if (l < min({a[3], i, j, k})) d[i][j][k][l + 1][m] += d[i][j][k][l][m];
    if (m < min({a[4], i, j, k, l})) d[i][j][k][l][m + 1] += d[i][j][k][l][m];
  }

  cout << d[a[0]][a[1]][a[2]][a[3]][a[4]] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
