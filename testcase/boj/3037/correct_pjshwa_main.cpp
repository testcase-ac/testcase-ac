#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4, MOD = 1e9 + 7;
int d[2][MAX + 1];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  d[1][0] = 1;
  for (int i = 2; i <= n; i++) {
    int s = 0;
    for (int j = 0; j <= k; j++) {
      s = (s + d[(i + 1) % 2][j]) % MOD;
      if (j >= i) s = (s + MOD - d[(i + 1) % 2][j - i]) % MOD;
      d[i % 2][j] = s;
    }
  }

  cout << d[n % 2][k] << '\n';
}
