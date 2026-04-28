#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1e9 + 7;
bool hole[MAX + 1][MAX + 1];
int d[MAX + 2][MAX + 2];

int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  while (k--) {
    int x, y;
    cin >> x >> y;
    hole[x][y] = true;
  }

  d[1][1] = 1;
  for (int j = 1; j <= m; j++) for (int i = 1; i <= n; i++) {
    if (hole[i][j]) continue;

    d[i][j] = (d[i][j] + d[i - 1][j]) % MOD;
    d[i][j] = (d[i][j] + d[i][j - 1]) % MOD;
    if (j & 1) d[i][j] = (d[i][j] + d[i - 1][j - 1]) % MOD;
    else d[i][j] = (d[i][j] + d[i + 1][j - 1]) % MOD;
  }
  cout << d[n][m] << '\n';
}
