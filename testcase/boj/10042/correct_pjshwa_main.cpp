#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 10007;

// 0: None, 1: J, 2: O, 3: JO,
// 4: I, 5: JI, 6: OI, 7: JOI
int d[8][MAX + 1];

void solve() {
  int n;
  string s;
  cin >> n >> s;

  d[1][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (s[i - 1] == 'J') d[1][i] = (d[1][i - 1] + d[3][i - 1] + d[5][i - 1] + d[7][i - 1]) % MOD;
    if (s[i - 1] == 'O') d[2][i] = (d[2][i - 1] + d[3][i - 1] + d[6][i - 1] + d[7][i - 1]) % MOD;
    if (s[i - 1] != 'I') d[3][i] = (d[1][i - 1] + d[2][i - 1] + d[3][i - 1] + d[5][i - 1] + d[6][i - 1] + d[7][i - 1]) % MOD;
    if (s[i - 1] == 'I') d[4][i] = (d[4][i - 1] + d[5][i - 1] + d[6][i - 1] + d[7][i - 1]) % MOD;
    if (s[i - 1] != 'O') d[5][i] = (d[1][i - 1] + d[3][i - 1] + d[4][i - 1] + d[5][i - 1] + d[6][i - 1] + d[7][i - 1]) % MOD;
    if (s[i - 1] != 'J') d[6][i] = (d[2][i - 1] + d[3][i - 1] + d[4][i - 1] + d[5][i - 1] + d[6][i - 1] + d[7][i - 1]) % MOD;
    d[7][i] = (d[1][i - 1] + d[2][i - 1] + d[3][i - 1] + d[4][i - 1] + d[5][i - 1] + d[6][i - 1] + d[7][i - 1]) % MOD;
  }

  if (s[n - 1] == 'J') cout << (d[1][n] + d[3][n] + d[5][n] + d[7][n]) % MOD;
  if (s[n - 1] == 'O') cout << (d[2][n] + d[3][n] + d[6][n] + d[7][n]) % MOD;
  if (s[n - 1] == 'I') cout << (d[4][n] + d[5][n] + d[6][n] + d[7][n]) % MOD;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
