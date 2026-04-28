#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
long long d[10001];
int main() {
  fast_io();

  d[0] = 1;
  d[3] = 3;
  d[6] = 13;
  for (int i = 9; i <= 10000; i += 3) d[i] = (5 * d[i - 3] + (MOD - 3) * d[i - 6] + d[i - 9]) % MOD;

  int t, n;
  cin >> t;

  while (t--) {
    cin >> n;
    cout << d[n] << '\n';
  }
}
