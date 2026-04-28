#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
int d[1001][9000];
int tc;

void solve() {
  int n;
  cin >> n;
  cout << "Case #" << ++tc << ": " << d[2 * n][9 * n] << '\n';
}

int main() {
  fast_io();

  for (int k = 0; k < 10; k++) d[1][k] = 1;
  for (int i = 2; i <= 1000; i++) {
    for (int j = 0; j <= 9 * i; j++) d[i][j] = d[i - 1][j];
    for (int j = 0; j <= 9 * i; j++) for (int k = 1; k < 10; k++) {
      if (j - k < 0) continue;
      d[i][j] = (d[i][j] + d[i - 1][j - k]) % MOD;
    }
  }

  int t;
  cin >> t;
  while (t--) solve();
}
