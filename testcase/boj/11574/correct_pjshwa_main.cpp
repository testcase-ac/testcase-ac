#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, MOD = 1e9 + 7;
ll d2[MAX + 1][MAX + 1], d3[MAX + 1][MAX + 1][MAX + 1];
int n;

void solvek2() {
  d2[0][0] = 1;
  for (int i = 1; i <= n; i++) for (int j = 0; j <= i; j++) {
    int k = i - j;
    int add1 = j > 0 ? (d2[i - 1][j - 1] * (i - j + 1)) % MOD : 0;
    int add2 = k > 0 ? (d2[i - 1][j] * (j + 1)) % MOD : 0;

    d2[i][j] = (d2[i][j] + add1) % MOD;
    d2[i][j] = (d2[i][j] + add2) % MOD;
  }

  int ans = 0;
  for (int j = 0; j <= n; j++) ans = (ans + d2[n][j]) % MOD;
  cout << ans << '\n';
}

void solvek3() {
  d3[0][0][0] = 1;
  for (int i = 1; i <= n; i++) for (int j = 0; j <= i; j++) for (int k = 0; j + k <= i; k++) {
    int l = i - j - k;
    int add1 = j > 0 ? (d3[i - 1][j - 1][k] * (i - j + 1)) % MOD : 0;
    int add2 = k > 0 ? (d3[i - 1][j][k - 1] * (i - k + 1)) % MOD : 0;
    int add3 = l > 0 ? (d3[i - 1][j][k] * (j + k + 1)) % MOD : 0;

    d3[i][j][k] = (d3[i][j][k] + add1) % MOD;
    d3[i][j][k] = (d3[i][j][k] + add2) % MOD;
    d3[i][j][k] = (d3[i][j][k] + add3) % MOD;
  }

  int ans = 0;
  for (int j = 0; j <= n; j++) for (int k = 0; k <= n; k++) ans = (ans + d3[n][j][k]) % MOD;
  cout << ans << '\n';
}

void solve() {
  int k;
  cin >> n >> k;
  if (k == 1) cout << "1\n";
  if (k == 2) solvek2();
  if (k == 3) solvek3();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
