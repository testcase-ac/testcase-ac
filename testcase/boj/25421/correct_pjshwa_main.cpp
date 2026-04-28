#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 987654321;
int d[MAX + 1][10];

void solve() {
  int n;
  cin >> n;
  for (int j = 1; j <= 9; j++) d[1][j] = 1;

  for (int i = 2; i <= n; i++) {
    for (int p = 1; p <= 9; p++) for (int j = p - 2; j <= p + 2; j++) {
      if (j < 1 || j > 9) continue;
      d[i][j] = (d[i][j] + d[i - 1][p]) % MOD;
    }
  }

  int ans = 0;
  for (int j = 1; j <= 9; j++) ans = (ans + d[n][j]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
