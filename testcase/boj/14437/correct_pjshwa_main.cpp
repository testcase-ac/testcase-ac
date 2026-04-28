#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
int d[2][3001];

void solve() {
  int k; string s;
  cin >> k >> s;
  int n = s.size();

  for (int j = 0; j <= 25; j++) d[1][j] = 1;
  for (int j = 1; j <= 3000; j++) d[1][j] = (d[1][j] + d[1][j - 1]) % MOD;

  for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= 3000; j++) {
      if (j >= 26) d[i % 2][j] = (d[(i - 1) % 2][j] - d[(i - 1) % 2][j - 26] + MOD) % MOD;
      else d[i % 2][j] = d[(i - 1) % 2][j];
    }
    for (int j = 1; j <= 3000; j++) d[i % 2][j] = (d[i % 2][j] + d[i % 2][j - 1]) % MOD;
  }
  
  cout << (d[n % 2][k] - d[n % 2][k - 1] + MOD) % MOD << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
