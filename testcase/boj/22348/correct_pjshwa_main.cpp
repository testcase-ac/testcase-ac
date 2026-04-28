#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, MAXV = 50000, MOD = 1e9 + 7;
int d[MAX + 1][MAXV + 1], s[MAX + 1][MAXV + 1];

void solve() {
  int a, b;
  cin >> a >> b;
  
  int ans = 0;
  for (int k = 1; k <= MAX; k++) {
    int all = k * (k + 1) / 2;
    if (all - b > a) continue;
    ans = (ans + s[k][a]) % MOD;
    if (all - b > 0) ans = (ans + MOD - s[k][all - b - 1]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  d[0][0] = 1;
  for (int i = 0; i < MAX; i++) for (int j = 0; j <= MAXV; j++) {
    if (j + (i + 1) <= MAXV) d[i + 1][j + (i + 1)] = (d[i + 1][j + (i + 1)] + d[i][j]) % MOD;
    d[i + 1][j] = (d[i + 1][j] + d[i][j]) % MOD;
  }

  for (int i = 0; i <= MAX; i++) {
    s[i][0] = d[i][0];
    for (int j = 1; j <= MAXV; j++) s[i][j] = (s[i][j - 1] + d[i][j]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
