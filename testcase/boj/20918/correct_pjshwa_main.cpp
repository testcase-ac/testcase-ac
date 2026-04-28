#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1010, MOD = 1e9 + 7;
int d[MAX + 10][MAX + 10], o[MAX + 10][MAX + 10], u[MAX + 10];

void solve() {
  int n, a, b;
  cin >> n >> a >> b;

  int ans = 0;
  if (a) ans = (d[n][b] - d[n][a - 1] + MOD) % MOD;
  else ans = d[n][b];
  cout << ans << '\n';
}

int last_k(int i, int j, int k) {
  int res;
  if (j - k < 0) res = o[i][j];
  else res = (o[i][j] + MOD - o[i][j - k]) % MOD;
  return res;
}

int main() {
  fast_io();

  for (int j = 0; j <= MAX; j++) o[1][j] = 1;

  for (int i = 2; i <= MAX; i++) {
    o[i][0] = u[0] = 1;
    for (int j = 1; j <= MAX; j++) {
      o[i][j] = (o[i][j - 1] + last_k(i - 1, j, i)) % MOD;
      u[j] = (o[i][j] + MOD - o[i][j - 1]) % MOD;
    }

    for (int j = 0; j < MAX; j++) {
      d[i - 1][j] = u[j];
      u[j + 1] = (u[j + 1] + MOD - u[j]) % MOD;
    }
    for (int j = 1; j <= MAX; j++) d[i - 1][j] = (d[i - 1][j] + d[i - 1][j - 1]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
