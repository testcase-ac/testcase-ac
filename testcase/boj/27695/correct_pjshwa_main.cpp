#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 9;
ll d[MAX + 1];

void solve() {
  int n; cin >> n;
  cout << d[n] << '\n';
}

int main() {
  fast_io();

  d[0] = 1;
  for (int i = 1; i <= MAX; i++) {
    if (i >= 1) d[i] = (d[i] + 1 * d[i - 1]) % MOD;
    if (i >= 2) d[i] = (d[i] + 2 * d[i - 2]) % MOD;
    if (i >= 3) d[i] = (d[i] + 3 * d[i - 3]) % MOD;
    if (i >= 4) d[i] = (d[i] + 5 * d[i - 4]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
