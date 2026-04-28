#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
int d[11][MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;

  int psum = k;
  for (int j = 1; j <= k; j++) d[1][j] = 1;
  for (int i = 2; i <= n; i++) {
    int csum = 0;
    for (int j = 1; j <= k; j++) {
      int msum = 0;
      for (int h = 2 * j; h <= k; h += j) msum = (msum + d[i - 1][h]) % MOD;
      d[i][j] = (psum + MOD - msum) % MOD;
      csum = (csum + d[i][j]) % MOD;
    }
    psum = csum;
  }

  cout << psum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
