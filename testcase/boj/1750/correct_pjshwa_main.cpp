#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 50, MOD = 1e7 + 3;
int a[MAX + 1], d[MAX + 1][100'001];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  d[1][a[1]] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= 100'000; j++) d[i][j] = d[i - 1][j];
    d[i][a[i]] = (d[i][a[i]] + 1) % MOD;

    for (int j = 1; j <= 100'000; j++) {
      int g = __gcd(j, a[i]);
      d[i][g] = (d[i][g] + d[i - 1][j]) % MOD;
    }
  }

  cout << d[n][1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
