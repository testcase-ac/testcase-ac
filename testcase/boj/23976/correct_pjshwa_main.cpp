#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2500, MOD = 1e9 + 7;
int d[2][MAX + 1][MAX + 1];

void solve() {
  int n, k;
  string s;
  cin >> n >> k >> s;

  if (s[0] == '0') d[1][0][0] = 1;
  else d[0][0][0] = 1;

  for (int i = 1; i < n; i++) for (int j = 0; j < k; j++) {
    d[0][i][j] = d[0][i - 1][j];
    if (j == 0) continue;
    if (s[i] == '0') {
      d[1][i][j] = (d[0][i - 1][j - 1] + d[1][i - 1][j - 1]) % MOD;
    }
    else {
      d[0][i][j] = (d[0][i][j] + d[0][i - 1][j - 1]) % MOD;
      d[0][i][j] = (d[0][i][j] + d[1][i - 1][j - 1]) % MOD;
    }
  }

  cout << (d[0][n - 1][k - 1] + d[1][n - 1][k - 1]) % MOD << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
