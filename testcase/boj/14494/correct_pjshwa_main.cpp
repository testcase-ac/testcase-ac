#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int d[1001][1001];
int main() {
  int n, m;
  cin >> n >> m;

  d[1][1] = 1;
  for (int i = 2; i <= n; i++) d[i][1] = 1;
  for (int i = 2; i <= m; i++) d[1][i] = 1;

  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= m; j++) {
      d[i][j] = (d[i][j] + d[i - 1][j]) % MOD;
      d[i][j] = (d[i][j] + d[i][j - 1]) % MOD;
      d[i][j] = (d[i][j] + d[i - 1][j - 1]) % MOD;
    }
  }

  cout << d[n][m] << '\n';
}
